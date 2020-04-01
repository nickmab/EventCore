#include "pch.h"

#include "TCPServer.h"

#include "TCPUtils.h"

namespace EventCore {

    TCPServer::TCPServer(
        ProtoParser::Protocol proto,
        EventProducer::EventCallbackFn evtCallback,
        ULONG inAddr, 
        USHORT listeningPort)
        : EventProducer(evtCallback)
        , mProtocol(proto)
    {
        mSockAddrIn.sin_family = AF_INET;
        mSockAddrIn.sin_port = htons(listeningPort);
        mSockAddrIn.sin_addr.S_un.S_addr = inAddr;
    }

    TCPServer::~TCPServer()
    {
        if (!mShutdown)
            Shutdown();
    }    

    bool TCPServer::Init()
    {
        if (mInitialized)
        {
            LOG_ERROR("Called 'Init()' after server was already initialized!");
            return false;
        }

        {
            WSADATA wsData;
            WORD version = MAKEWORD(2, 2);
            if (int startupErr = WSAStartup(version, &wsData); startupErr != 0)
            {
                std::string msg = "Call to WSAStartup failed.";
                TCPError(msg, startupErr);
                return false;
            }
        }

        mListeningSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (mListeningSocket == INVALID_SOCKET)
        {
            std::string msg = "Unable to create listening socket.";
            TCPError(msg);
            return false;
        }

        if (bind(mListeningSocket, (sockaddr*)&mSockAddrIn, sizeof(mSockAddrIn)) == SOCKET_ERROR)
        {
            std::string msg = "Failed to bind listening socket.";
            TCPError(msg);
            return false;
        }

        if (listen(mListeningSocket, SOMAXCONN) == SOCKET_ERROR)
        {
            std::string msg = "Failed to start listening on listening socket.";
            TCPError(msg);
            return false;
        }

        // OK we are finally listening. Add the listening socket to the set and off we go.
        LOG_INFO("Successfully initialized server.");
        FD_ZERO(&mFDSet);
        FD_SET(mListeningSocket, &mFDSet);
        mInitialized = true;
        mRunning = true;
        return true;
    }

    TCPDataInterface* TCPServer::FindClientInClientMapBySocket(SOCKET sock)
    {
        TCPDataInterface* maybeFound = nullptr;
        for (auto& sIdToData : mClientMap)
        {
            if (sIdToData.second->mSession.GetSocket() == sock)
            {
                maybeFound = sIdToData.second.get();
                break;
            }
        }
        return maybeFound;
    }

    bool TCPServer::OnUpdate()
    {
        if (!mRunning)
        {
            LOG_WARN("Server is not running! Doing nothing.");
            return false;
        }

        // First see if we have anything queued to write out to existing clients.
        // We drop the client if we can no longer write to them / if there is some kind of error.
        std::vector<TCPSession::SessionId> mapItemsToErase;
        for (auto& sIdToData : mClientMap)
        {
            const auto sessionId = sIdToData.first;
            auto& session = sIdToData.second->mSession;
            auto& parser = sIdToData.second->mParser;
            if (parser->HasData() && !parser->WriteTo(session))
            {
                LOG_WARN("Error trying to write to client; dropping it.");
                
                FD_CLR(session.GetSocket(), &mFDSet);
                
                RaiseEvent(new TCPConnectionEvent(this, sessionId, TCPConnectionEvent::Type::ClientDisconnected));
                mapItemsToErase.push_back(sessionId);
            }
        }

        for (auto sessionId : mapItemsToErase)
            mClientMap.erase(sessionId);

        // Then we call "select" to see if there's any data anywhere.
        fd_set copyOfExistingFDSet = mFDSet;
        timeval zeroTimeOut = { 0, 0 };
        int socketCount = select(0, &copyOfExistingFDSet, nullptr, nullptr, &zeroTimeOut);

        if (socketCount == SOCKET_ERROR)
        {
            std::string msg = "Error calling select on listening socket.";
            TCPError(msg);
            return false;
        }

        for (int i = 0; i < socketCount; i++)
        {
            SOCKET sock = copyOfExistingFDSet.fd_array[i];
            
            if (sock == mListeningSocket)
            {
                // If we have data on the listening socket, we accept a new client.
                SOCKET newClient = accept(mListeningSocket, nullptr, nullptr);

                if (newClient == INVALID_SOCKET)
                {
                    std::string msg = "Error calling accept on listening socket.";
                    TCPError(msg);
                    return false;
                }

                FD_SET(newClient, &mFDSet);

                // OK I've accidentally made this kind of awkward because we need to construct the object
                // to get a unique session id, but we want to key the map of the instances by session id. heh.
                // easily fixed, but leaving it like this for now.
                ProtoParser* parser = ProtoParser::New(mProtocol, mCallback);
                if (!parser)
                {
                    LOGF_ERROR("Unrecognised protocol; unable to create parser: {}", mProtocol);
                    return false;
                }
                TCPDataInterface* newDataInterface = new TCPDataInterface(parser, newClient);
                const auto sessionId = newDataInterface->mSession.GetSessionId();
                mClientMap.emplace(sessionId, newDataInterface);
                
                RaiseEvent(new TCPConnectionEvent(this, sessionId, TCPConnectionEvent::Type::ClientConnected));
            }
            else
            {
                // If we have data on an existing socket of an existing session, recv from it.
                // As long as we can read without blocking (i.e. there is data there),
                // keep filling up the session buffer...
                
                TCPDataInterface* clientData = FindClientInClientMapBySocket(sock);
                if (!clientData)
                {
                    LOG_CRITICAL("Tried to read data from unknown socket/session!");
                    Shutdown();
                    return false;
                }
                else
                {
                    auto& session = clientData->mSession;
                    const auto sessionId = session.GetSessionId();
                    if (!session.Recv())
                    {
                        LOG_ERROR("Some kind of error recv'ing from socket. Deleting client.");
                        
                        RaiseEvent(new TCPConnectionEvent(this, sessionId, TCPConnectionEvent::Type::ClientDisconnected));

                        FD_CLR(sock, &mFDSet);
                        mClientMap.erase(sessionId);
                    }
                    else if (session.BufferHasData())
                    {
                        if (!clientData->mParser->ConsumeFrom(session))
                        {
                            LOG_ERROR("Some kind of error parsing socket data. Deleting client.");
                            FD_CLR(sock, &mFDSet);
                            mClientMap.erase(sessionId);
                        }
                    }
                }
            }
        }        

        return true;
    }

    bool TCPServer::QueueOutgoingMessage(TCPSession::SessionId sessionId, const ProtoMsgVariant& msg)
    {
        auto it = mClientMap.find(sessionId);
        if (it == mClientMap.end())
            return false;
        return it->second->mParser->QueueMessageToWrite(msg);
    }

    void TCPServer::Shutdown()
    {
        // the mClientSessions going out of scope should automatically call destructors to free memory...
        shutdown(mListeningSocket, SD_BOTH);
        // Try to do a graceful disconnect ...but doesn't seem to work very well.
        const int optVal = 1000;
        const int optLen = sizeof(int);
        setsockopt(mListeningSocket, SOL_SOCKET, SO_DONTLINGER, (char*)&optVal, optLen);
        closesocket(mListeningSocket);
        WSACleanup();
        mRunning = false;
        mShutdown = true;
    }

}