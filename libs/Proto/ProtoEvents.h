#pragma once

#include "Core/Events/Event.h"
#include "TCP/TCPSession.h"
#include "Proto/DemoProto/DemoProto.pb.h"
#include "Proto/MathProto/MathProto.pb.h"

namespace EventCore {

    class EventProducer;

    // YUCK.
    using ProtoMsgVariant = std::variant<
        demoproto::NumericMessage,
        demoproto::TextualMessage,
        demoproto::WrappedMessage,
        mathproto::ArithmeticRequest,
        mathproto::ArithmeticResponse,
        mathproto::WrappedMessage>;

    class ProtoMessageReceivedEvent : public Event
    {
    public:
        static ProtoMessageReceivedEvent* New(
            const EventProducer* sender, 
            TCPSession::SessionId source, 
            const ProtoMsgVariant&);
        
        ProtoMessageReceivedEvent(
            const EventProducer* sender, 
            TCPSession::SessionId source, 
            ProtoMsgVariant*);

        inline virtual Event::Type GetType() const override { return Event::Type::ProtoMessageReceived; }
        inline virtual const char* const GetName() const override { return "ProtoMessageReceivedEvent"; } 

        virtual std::string ToString() const override;
        
        inline TCPSession::SessionId GetSessionId() const { return mSource; }

#ifdef GetMessage
#undef GetMessage // this is some totally random windows macro name.
#endif
        inline const ProtoMsgVariant& GetMessage() const { return *mMessage; }

    private: 
        TCPSession::SessionId mSource;
        std::unique_ptr<ProtoMsgVariant> mMessage;
    };

}
