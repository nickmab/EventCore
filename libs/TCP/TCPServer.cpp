#include "Core/Application.h"
#include "TCPServer.h"
#include "TCPUtils.h"
#include "Core/Logger.h"

#include <sstream>
#include <tuple>

namespace EventCore {

	TCPServer::TCPServer(ParserFactoryFn makeNewParser, ULONG inAddr, USHORT listeningPort)
		: mMakeNewParser(makeNewParser)
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

	TCPServer::ClientDataInterface::ClientDataInterface(ProtoParser* parser, SOCKET sock, size_t initialRecvBufSize)
		: mSession(sock, initialRecvBufSize)
		, mParser(parser)
	{
		Application::Get().RegisterEventProducer(parser);
	}

	TCPServer::ClientDataInterface::~ClientDataInterface()
	{
		Application::Get().UnregisterEventProducer(mParser.get());
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

	bool TCPServer::OnUpdate()
	{
		if (!mRunning)
		{
			LOG_WARN("Server is not running! Doing nothing.");
			return false;
		}

		// First see if we have anything queued to write out to existing clients.
		std::vector<SOCKET> clientsToDrop;
		for (auto& sockAndData : mClientMap)
		{
			auto& session = sockAndData.second.mSession;
			auto& parser = sockAndData.second.mParser;
			if (parser->HasData() && !parser->WriteTo(session))
			{
				LOG_WARN("Error trying to write to client; dropping it.");
				clientsToDrop.push_back(sockAndData.first);
			}
		}

		for (auto& sock : clientsToDrop)
		{
			mClientMap.erase(sock);
			FD_CLR(sock, &mFDSet);
		}

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
				mClientMap.emplace(
					std::piecewise_construct,
					/* map key */
					std::forward_as_tuple(newClient),
					/* constructor args for ClientDataInterface */
					std::forward_as_tuple(
						mMakeNewParser(),
						newClient)
					);
				
				demoproto::TextualMessage msg;
				msg.set_a_sentence("Hello from the server! Sending a number too...");
				bool success = QueueWriteData(newClient, msg);
				LOGF_WARN("Success? {}", success);
				demoproto::NumericMessage msg2;
				msg2.set_an_integer(12345);
				msg2.set_a_double(-4483.9);
				success = QueueWriteData(newClient, msg2);
				LOGF_WARN("Success? {}", success);
			}
			else
			{
				// If we have data on an existing socket of an existing session, recv from it.
				// As long as we can read without blocking (i.e. there is data there),
				// keep filling up the session buffer...
				auto clientData = mClientMap.find(sock);
				if (clientData == mClientMap.end())
				{
					LOG_WARN("Tried to read data from unknown socket/session!");
				}
				else
				{
					auto& session = clientData->second.mSession;
					if (!session.Recv())
					{
						LOG_WARN("Some kind of error recv'ing from socket. Deleting client.");
						FD_CLR(sock, &mFDSet);
						mClientMap.erase(sock);
					}
					else if (session.BufferHasData())
					{
						if (!clientData->second.mParser->ConsumeFrom(session))
						{
							LOG_ERROR("Some kind of error parsing socket data. Deleting client.");
							FD_CLR(sock, &mFDSet);
							mClientMap.erase(sock);
						}
					}
				}
			}
		}		

		return true;
	}

	bool TCPServer::QueueWriteData(SOCKET sock, const ProtoMsgVariant& msg)
	{
		auto it = mClientMap.find(sock);
		if (it == mClientMap.end())
			return false;
		return it->second.mParser->QueueMessageToWrite(msg);
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