#pragma once

#include <WS2tcpip.h>

#include <map>
#include <memory>

#include "TCPSession.h"

#include "Core/Event.h"
#include "Proto/ProtoParser.h"
#include "Proto/DemoProto/DemoProtoParser.h"

namespace EventCore {

	static const ULONG DEFAULT_IN_ADDR = INADDR_ANY;
	static const USHORT DEFAULT_LISTENING_PORT = 54000;

	// This needs to be both a producer and consumer of events.
	// Might eventually turn it into an abstract class and make something else impl a protocol...
	class TCPServer : public EventProducer
	{
	public:
		using ParserFactoryFn = std::function<ProtoParser * (void)>;
		
		TCPServer(
			EventProducer::EventCallbackFn, 
			ParserFactoryFn, 
			ULONG inAddr = DEFAULT_IN_ADDR, 
			USHORT listeningPort = DEFAULT_LISTENING_PORT);
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
		bool QueueWriteData(SOCKET, const ProtoMsgVariant&);

	private:
		sockaddr_in mSockAddrIn;
		SOCKET mListeningSocket{0};
		fd_set mFDSet{0};

		ParserFactoryFn mMakeNewParser;
		// This is the thing that actually _owns_ the parser (and the events it produces/consumes).
		struct ClientDataInterface
		{
			ClientDataInterface(ProtoParser*, SOCKET, size_t initialRecvBufSize = 1024);
			~ClientDataInterface();
			TCPSession mSession;
			std::unique_ptr<ProtoParser> mParser;
		};
		std::map<SOCKET, ClientDataInterface> mClientMap;
		
		bool mInitialized{false};
		bool mRunning{false};
		bool mShutdown{false};
	};

}