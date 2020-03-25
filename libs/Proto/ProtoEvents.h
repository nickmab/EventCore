#pragma once

#include <WS2tcpip.h>

#include <memory>

#include "Core/Event.h"
#include "ProtoParser.h"
#include "TCP/TCPSession.h"

namespace EventCore {

	class OnProtoMessageReceived : public Event
	{
	public:
		OnProtoMessageReceived(TCPSession::SessionId source, ProtoMsgVariant*);

		inline virtual Event::Type GetType() const override { return Event::Type::OnProtoMessageReceived; }
		inline virtual const char* const GetName() const override { return "OnProtoMessageReceivedEvent"; } 

		virtual std::string ToString() const override; 

	private: 
		TCPSession::SessionId mSource;
		std::unique_ptr<ProtoMsgVariant> mMessage;
	};

}
