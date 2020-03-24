#pragma once

#include "ProtoEvents.h"

#include <sstream>

namespace EventCore {

	OnProtoMessageReceived::OnProtoMessageReceived(TCPSession::SessionId source, std::shared_ptr<ProtoMsgVariant> msg)
		: mSource(source)
		, mMessage(msg)
	{
	}

	std::string OnProtoMessageReceived::ToString() const
	{
		std::stringstream ss;
		// This is possibly the worst line of code I have ever written...
		// It basically relies on the concrete message type encapsulated behind the
		// ProtoMsgVariant having a DebugString() -> std::string method.
		// (like generated protobuf messages do).
		ss << "OnProtoMessageReceivedEvent: source session ID: " << mSource
			<< "message: " << std::visit(
				[](auto&& arg) -> std::string&& { return arg.DebugString(); },
				*mMessage);
		return ss.str();
	}

}
