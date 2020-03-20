#include "TCPClient.h"
#include "TCPUtils.h"

#include <sstream>
#include <iostream>

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
			std::cout << "Called 'Init()' after client was already initialized!" << std::endl;
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

		std::cout << "Successfully initialized client and connected to server." << std::endl;
		mServerSession.reset(new TCPSession(sock));
		mInitialized = true;
		mRunning = true;
		QueueWriteData("Hello from a client!");
		return true;
	}

	bool TCPClient::OnUpdate()
	{
		if (!mRunning)
		{
			std::cout << "Client is not running! Doing nothing." << std::endl;
			return false;
		}

		// First see if we have anything queued to write out to existing clients.
		for (auto& str : mQueuedWriteData)
		{
			if (!mServerSession->Send(str))
			{
				std::cout << "Some kind of error sending data to server. Shutting down." << std::endl;
				Shutdown();
				return false;
			}
		}

		mQueuedWriteData.clear();

		// Now see if there's anything to read...
		if (!mServerSession->Recv())
		{
			std::cout << "Some kind of error recv'ing from socket. Disconnecting." << std::endl;
			Shutdown();
			return false;
		}

		if (mServerSession->BufferHasData())
		{
			std::cout << "Received the following from server..." << std::endl;
			std::cout << mServerSession->GetAllRecvBufferContents() << std::endl;
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
		mQueuedWriteData.emplace_back(data);
	}

}