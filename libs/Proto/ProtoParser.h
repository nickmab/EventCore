#pragma once

#include "Core/Events/EventQueue.h"
#include "TCP/TCPSession.h"

namespace EventCore {


    class ProtoParser : public EventProducer
    {
    public:
        
        enum class Protocol
        {
            DemoProto = 0,
            MathProto
        };
        
        static ProtoParser* New(Protocol);

        virtual ~ProtoParser() {}
        
        // false indicates error.
        virtual bool ConsumeFrom(TCPSession&) = 0;
        virtual bool QueueMessageToWrite(const ProtoMsgVariant&) = 0;
        virtual bool WriteTo(TCPSession&) = 0;

        // this *should* really be const, but for practial impl reasons
        // right now it is not. see DemoProtoParser implementation.
        virtual bool HasData() = 0;
    };

}