#include "pch.h"

#include "ProtoParser.h"

#include "Proto/DemoProto/DemoProtoParser.h"
#include "Proto/MathProto/MathProtoParser.h"

namespace EventCore {

    ProtoParser* ProtoParser::New(Protocol proto)
    {
        switch (proto)
        {
        case Protocol::DemoProto:
            return new DemoProtoParser();
        case Protocol::MathProto:
            return new MathProtoParser();
        default:
            ASSERTF(false, "This should be unreachable! Unknown proto: {}", proto);
            return nullptr;
        }
    }
    
}
