#include "TCPClient.h"
#include "TCPUtils.h"
#include "Core/Logger.h"

#include <sstream>

#include "Proto/DemoProto/DemoProto.pb.h"

namespace EventCore {

	TCPClient::TCPClient(const char* serverAddr, USHORT serverPort)
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
		QueueWriteData("Hello from a client!");
		demoproto::NumericMessage msg;
		msg.set_an_integer(6123);
		msg.set_a_double(42.1);
		std::string debug = msg.DebugString();
		QueueWriteData(debug);
		std::string strOut;
		msg.SerializeToString(&strOut);
		std::cout << strOut << std::endl;
		std::cout << strOut.length() << std::endl;
		std::cout << strOut.size() << std::endl;
		QueueWriteData(strOut);
		return true;
	}

	bool TCPClient::OnUpdate()
	{
		if (!mRunning)
		{
			LOG_WARN("Client is not running! Doing nothing.");
			return false;
		}

		// First see if we have anything queued to write out to existing clients.
		for (auto& str : mQueuedWriteData)
		{
			LOGF_TRACE("Try to send: {}", str);
			if (!mServerSession->Send(str))
			{
				LOG_CRITICAL("Some kind of error sending data to server. Shutting down.");
				Shutdown();
				return false;
			}
		}

		mQueuedWriteData.clear();

		// Now see if there's anything to read...
		if (!mServerSession->Recv())
		{
			LOG_CRITICAL("Some kind of error recv'ing from socket. Disconnecting.");
			Shutdown();
			return false;
		}

		if (mServerSession->BufferHasData())
		{
			LOG_INFO("Received the following from server...");
			LOG_INFO(mServerSession->GetAllRecvBufferContents());
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

	void TCPClient::QueueWriteData(const std::string& data)
	{
		LOGF_TRACE("Queueing: {}", data);
		mQueuedWriteData.emplace_back(data);
	}

}