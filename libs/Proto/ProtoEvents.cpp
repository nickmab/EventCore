#include "pch.h"

#include "ProtoEvents.h"

namespace EventCore {

	ProtoMessageReceivedEvent* ProtoMessageReceivedEvent::New(
		const EventProducer* sender,
		TCPSession::SessionId source,
		const ProtoMsgVariant& msg)
	{
		return new ProtoMessageReceivedEvent(sender, source, new ProtoMsgVariant(msg));
	}

	ProtoMessageReceivedEvent::ProtoMessageReceivedEvent(
		const EventProducer* sender,
		TCPSession::SessionId source,
		ProtoMsgVariant* msg)
		: Event(sender)
		, mSource(source)
		, mMessage(msg)
	{
	}

	std::string ProtoMessageReceivedEvent::ToString() const
	{
		std::stringstream ss;
		// This is possibly the worst line of code I have ever written...
		// It basically relies on the concrete message type encapsulated behind the
		// ProtoMsgVariant having a DebugString() -> std::string method.
		// (like generated protobuf messages do).
		ss << "OnProtoMessageReceivedEvent: source session ID: " << mSource
			<< " message: " << std::visit(
				[](auto& arg) -> std::string { return arg.DebugString(); },
				*mMessage);
		return ss.str();
	}

}