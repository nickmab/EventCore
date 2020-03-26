#pragma once

#include "Core/Event.h"
#include "TCP/TCPSession.h"
#include "DemoProto/DemoProto.pb.h"
#include "MathProto/MathProto.pb.h"

#include <variant>

namespace EventCore {

	// ALL potential message types from all protocols must be 
	// listed in this variant.
	using ProtoMsgVariant = std::variant<
		demoproto::NumericMessage,
		demoproto::TextualMessage,
		demoproto::WrappedMessage,
		mathproto::ArithmeticRequest,
		mathproto::ArithmeticResponse,
		mathproto::WrappedMessage>;

	class ProtoParser : public EventProducer
	{
	public:
		using ParserFactoryFn = std::function<ProtoParser * (void)>;
		
		ProtoParser(EventProducer::EventCallbackFn);
		virtual ~ProtoParser() {}
		
		// false indicates error.
		virtual bool ConsumeFrom(TCPSession&) = 0;
		virtual bool QueueMessageToWrite(const ProtoMsgVariant&) = 0;
		virtual bool WriteTo(TCPSession&) = 0;

		// this *should* really be const, but for practial impl reasons
		// right now it is not. see DemoProtoParser implementation.
		virtual inline bool HasData() = 0;
	};

}