#pragma once

#include "TCP/TCPSession.h"
#include "Proto/ProtoEvents.h"
#include "Proto/ProtoParser.h"

using namespace mathproto;

namespace EventCore {

    class MathProtoParser
        : public ProtoParser // which is also an EventProducer.
    {
    public:

        static ProtoParser* New();

        // false indicates error.
        virtual bool ConsumeFrom(TCPSession&) override;
        // provide one of the "concrete" message types (e.g. ArithmeticRequest, ArithmeticResponse)
        // and this method will automatically construct and queue a WrappedMessage containing
        // the correct "oneof" field to send over the wire.
        virtual bool QueueMessageToWrite(const ProtoMsgVariant&) override;
        virtual bool WriteTo(TCPSession&) override;

        virtual bool HasData() override;

    private:
        // these are used for i/o buffering and caching, saves you
        // repeatedly creating the same objects over and over. The protobuf
        // docs themselves suggest reusing message instances. 
        std::stringstream mInputBuffer;
        int mNextInputMessageSize{ 0 };
        std::stringstream mOutputBuffer;
    };

}