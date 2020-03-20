#pragma once

#include <WS2tcpip.h>

#include <memory>
#include <string>
#include <vector>

#include "TCPSession.h"

namespace EventCore {

	static const char* DEFAULT_SERVER_ADDR = "127.0.0.1";
	static const USHORT DEFAULT_SERVER_PORT = 54000;
	
	// This needs to be both a producer and consumer of events.
	// Might eventually turn it into an abstract class and make something else impl a protocol...
	class TCPClient
	{
	public:
		TCPClient(const char* serverAddr = DEFAULT_SERVER_ADDR, USHORT serverPort = DEFAULT_SERVER_PORT);
		~TCPClient();

		// For the below public methods, if an error is encountered it will return false
		// and also call "void EventCore::TCPError()" to fetch and log the error/reason.

		// Create the socket and connect.
		// If success, mRunning will be set to true and subsequent calls to OnUpdate 
		// will allow us to read and write data etc.
		bool Init();
		bool OnUpdate();
		
		void Shutdown();

		// temporary...
		void QueueWriteData(const std::string&);

	private:
		sockaddr_in mSockAddrIn;
		std::unique_ptr<TCPSession> mServerSession;
		bool mInitialized{false};
		bool mRunning{false};
		bool mShutdown{false};

		// temporary
		std::vector<std::string> mQueuedWriteData;
	};

}