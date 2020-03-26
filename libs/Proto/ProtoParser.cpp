#include "ProtoParser.h"

#include "Proto/DemoProto/DemoProtoParser.h"
#include "Proto/MathProto/MathProtoParser.h"

namespace EventCore {

	ProtoParser* ProtoParser::New(Protocol proto, EventProducer::EventCallbackFn callback)
	{
		switch (proto)
		{
		case Protocol::DemoProto:
			return new DemoProtoParser(callback);
		case Protocol::MathProto:
			return new MathProtoParser(callback);
		default:
			ASSERTF(false, "This should be unreachable! Unknown proto: {}", proto);
			return nullptr;
		}
	}
	
	ProtoParser::ProtoParser(EventProducer::EventCallbackFn callback)
		: EventProducer(callback)
	{
	}

}
