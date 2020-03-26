#pragma once

#include <WS2tcpip.h>

#include "TCPSession.h"
#include "Proto/ProtoParser.h"

#include <memory>

namespace EventCore {

	// This is the thing that actually _owns_ the parser (and the events it produces/consumes).
	struct TCPDataInterface
	{
		TCPDataInterface(ProtoParser*, SOCKET, size_t initialRecvBufSize = 1024);
		~TCPDataInterface();
		TCPSession mSession;
		std::unique_ptr<ProtoParser> mParser;
	};

}