#include "pch.h"

#include "TCPDataInterface.h"

#include "Core/Application.h"

namespace EventCore {

	TCPDataInterface::TCPDataInterface(ProtoParser* parser, SOCKET sock, size_t initialRecvBufSize)
		: mSession(sock, initialRecvBufSize)
		, mParser(parser)
	{
		Application::Get().RegisterEventProducer(parser);
	}

	TCPDataInterface::~TCPDataInterface()
	{
		Application::Get().UnregisterEventProducer(mParser.get());
	}

}