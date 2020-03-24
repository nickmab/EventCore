#include "TCPClient.h"
#include "TCPUtils.h"
#include "Core/Logger.h"

#include <sstream>

#include "Proto/DemoProto/DemoProto.pb.h"

namespace EventCore {

	TCPClient::TCPClient(ProtoParser* parser, const char* serverAddr, USHORT serverPort)
		: mParser(parser)
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

		LOG_INFO("Successfully initialized client and connected to server.");
		mServerSession.reset(new TCPSession(sock));
		mInitialized = true;
		mRunning = true;
		// QueueWriteData("Hello from a client!");
		demoproto::NumericMessage msg;
		msg.set_an_integer(6123);
		msg.set_a_double(42.1);
		LOG_WARN("Calling...");
		bool success = QueueWriteData(msg);
		LOGF_WARN("Returned {}", success);
		demoproto::TextualMessage msg2;
		LOG_WARN("Making a fresh juan");
		msg2.set_a_sentence("I got the message!");
		msg2.set_is_interesting(false);
		LOGF_WARN("Calling again, {}", msg2.DebugString());
		success = QueueWriteData(msg2);
		LOGF_WARN("Returned again {}", success);
		return true;
	}

	bool TCPClient::OnUpdate()
	{
		if (!mRunning)
		{
			LOG_WARN("Client is not running! Doing nothing.");
			return false;
		}

		if (mParser->HasData() && !mParser->WriteTo(*mServerSession))
		{
			LOG_CRITICAL("Some kind of error sending data to server. Shutting down.");
			Shutdown();
			return false;
		}

		// Now see if there's anything to read...
		if (!mServerSession->Recv())
		{
			LOG_CRITICAL("Some kind of error recv'ing from socket. Disconnecting.");
			Shutdown();
			return false;
		}

		if (mServerSession->BufferHasData())
		{
			if (!mParser->ConsumeFrom(*mServerSession))
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
		WSACleanup();
		mRunning = false;
		mShutdown = true;
	}

	bool TCPClient::QueueWriteData(const ProtoMsgVariant& msg)
	{
		return mParser->QueueMessageToWrite(msg);
	}

}