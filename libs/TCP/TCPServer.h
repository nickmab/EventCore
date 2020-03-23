#pragma once

#include <WS2tcpip.h>

#include <map>
#include <memory>
#include <string>

#include "TCPSession.h"

#include "Proto/DemoProto/DemoProtoParser.h"

namespace EventCore {

	static const ULONG DEFAULT_IN_ADDR = INADDR_ANY;
	static const USHORT DEFAULT_LISTENING_PORT = 54000;

	// This needs to be both a producer and consumer of events.
	// Might eventually turn it into an abstract class and make something else impl a protocol...
	class TCPServer
	{
	public:
		TCPServer(ULONG inAddr = DEFAULT_IN_ADDR, USHORT listeningPort = DEFAULT_LISTENING_PORT);
		~TCPServer();
		
		// For the below public methods, if an error is encountered it will return false
		// and also call "void EventCore::TCPError()" to fetch and log the error/reason.
		
		// Create the listening socket, bind and listen.
		// If success, mRunning will be set to true and subsequent calls to OnUpdate 
		// will allow us to accept incoming client connections etc.
		bool Init();
		bool OnUpdate();
		
		void Shutdown();

		// temporary...
		bool QueueWriteData(SOCKET, const DemoProtoParser::MsgVariant&);

	private:
		sockaddr_in mSockAddrIn;
		SOCKET mListeningSocket{0};
		fd_set mFDSet{0};

		struct ClientDataInterface
		{
			ClientDataInterface(SOCKET, size_t initialRecvBufSize = 1024);
			TCPSession mSession;
			DemoProtoParser mParser;
		};
		std::map<SOCKET, ClientDataInterface> mClientMap;
		
		bool mInitialized{false};
		bool mRunning{false};
		bool mShutdown{false};
	};

}