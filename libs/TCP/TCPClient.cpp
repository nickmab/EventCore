#include "pch.h"

#include "TCPClient.h"

#include "TCPUtils.h"

namespace EventCore {

    TCPClient::TCPClient(
        ProtoParser::Protocol proto,
        const char* serverAddr, 
        USHORT serverPort)
        : EventProducer()
        , mProtocol(proto)
    {
        mSockAddrIn.sin_family = AF_INET;
        mSockAddrIn.sin_port = htons(serverPort);
        inet_pton(AF_INET, serverAddr, &mSockAddrIn.sin_addr);
    }

    TCPClient::~TCPClient()
    {
        if (!mShutdown)
            Shutdown();
    }
    
    bool TCPClient::Init()
    {
        if (mInitialized)
        {
            LOG_ERROR("Called 'Init()' after client was already initialized!");
            return false;
        }

        {
            WSADATA wsData;
            WORD version = MAKEWORD(2, 2);
            if (const int startupErr = WSAStartup(version, &wsData); startupErr != 0)
            {
                std::string msg = "Call to WSAStartup failed.";
                TCPError(msg, startupErr);
                return false;
            }
        }

        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET)
        {
            std::string msg = "Unable to create socket.";
            TCPError(msg);
            return false;
        }

        const int connResult = connect(sock, (sockaddr*)&mSockAddrIn, sizeof(mSockAddrIn));
        if (connResult == SOCKET_ERROR)
        {
            std::string msg = "Unable to connect to server.";
            TCPError(msg);
            closesocket(sock);
            return false;
        }

        ProtoParser* parser = ProtoParser::New(mProtocol);
        if (!parser)
        {
            LOGF_ERROR("Unrecognised protocol; unable to create parser: {}", mProtocol);
            closesocket(sock);
            return false;
        }

        TCPDataInterface* newInterface = new TCPDataInterface(parser, sock);
        mDataInterface.reset(newInterface);

        LOG_INFO("Successfully initialized client and connected to server.");
        RaiseEvent(new TCPConnectionEvent(this, newInterface->mSession.GetSessionId(), 
            TCPConnectionEvent::Type::ServerConnected));

        mInitialized = true;
        mRunning = true;
        return true;
    }

    bool TCPClient::OnUpdate()
    {
        if (!mRunning)
        {
            LOG_WARN("Client is not running! Doing nothing.");
            return false;
        }

        auto& parser = mDataInterface->mParser;
        auto& session = mDataInterface->mSession;
        if (parser->HasData() && !parser->WriteTo(session))
        {
            LOG_CRITICAL("Some kind of error sending data to server. Shutting down.");
            Shutdown();
            return false;
        }

        // Now see if there's anything to read...
        if (!session.Recv())
        {
            LOG_CRITICAL("Some kind of error recv'ing from socket. Disconnecting.");
            Shutdown();
            return false;
        }

        if (session.BufferHasData())
        {
            if (!parser->ConsumeFrom(session))
            {
                LOG_ERROR("Some kind of error parsing socket data. Shutting down.");
                Shutdown();
                return false;
            }
        }

        return true;
    }

    void TCPClient::Shutdown()
    {
        // the mServerSession going out of scope should automatically call 
        // destructors to free memory and close the socket.
        RaiseEvent(new TCPConnectionEvent(this, mDataInterface->mSession.GetSessionId(),
            TCPConnectionEvent::Type::ServerDisconnected));
        
        WSACleanup();
        mRunning = false;
        mShutdown = true;
    }

    bool TCPClient::QueueOutgoingMessage(const ProtoMsgVariant& msg)
    {
        return mDataInterface->mParser->QueueMessageToWrite(msg);
    }

}