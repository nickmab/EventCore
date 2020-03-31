#include <pch.h>

#include "EventProfiler.h"

namespace EventCore {
    Application* CreateApplication(int argc, char* argv[])
    {
        return new ::EventProfiler();
    }
}

using namespace EventCore;

void EventProfiler::Init()
{
    mTickEventProducer.reset(new TickEventProducer(5));
    RegisterEventProducer(mTickEventProducer.get());

    mSpamGenerator.reset(new SpamGenerator(1000));
    RegisterEventProducer(mSpamGenerator.get());
    RegisterEventConsumer(mSpamGenerator.get());

    mAllEventConsumer.reset(new AllEventConsumer());
    RegisterEventConsumer(mAllEventConsumer.get());
}

void EventProfiler::OnUpdate()
{
}

SpamGenerator::SpamGenerator(unsigned maxIterations)
    : EventConsumer()
    , EventProducer()
    , mMaxIterations(maxIterations)
{
    mEventRaiserDispatchTable[0] = [this]() { this->RaiseEvent(new TCPClientConnectedEvent(nullptr, 0)); };
    mEventRaiserDispatchTable[1] = [this]() { this->RaiseEvent(new TCPClientDisconnectedEvent(nullptr, 0)); };
    mEventRaiserDispatchTable[2] = [this]() { this->RaiseEvent(new TCPServerConnectedEvent(nullptr, 0)); };
    mEventRaiserDispatchTable[3] = [this]() { this->RaiseEvent(new TCPServerDisconnectedEvent(nullptr, 0)); };
    
    mEventRaiserDispatchTable[4] = [this]() { 
        demoproto::WrappedMessage wrapped;
        demoproto::NumericMessage& msg = *wrapped.mutable_numeric_message();
        msg.set_a_double(9.0);
        msg.set_an_integer(3);
        this->RaiseEvent(ProtoMessageReceivedEvent::New(nullptr, 0, wrapped)); 
    };
    mEventRaiserDispatchTable[5] = [this]() {
        demoproto::WrappedMessage wrapped;
        demoproto::TextualMessage& msg = *wrapped.mutable_textual_message();
        msg.set_a_sentence("Hello, world");
        msg.set_is_interesting(true);
        this->RaiseEvent(ProtoMessageReceivedEvent::New(nullptr, 0, wrapped));
    };
    mEventRaiserDispatchTable[6] = [this]() {
        
        mathproto::WrappedMessage wrapped;
        mathproto::ArithmeticRequest msg = *wrapped.mutable_arithmetic_request();
        msg.set_lhs(3.0);
        msg.set_op(mathproto::ArithmeticOperator::TIMES);
        msg.set_rhs(7.6);
        msg.set_request_id(1);
        this->RaiseEvent(ProtoMessageReceivedEvent::New(nullptr, 0, wrapped));
    };
    mEventRaiserDispatchTable[7] = [this]() {
        mathproto::WrappedMessage wrapped; 
        mathproto::ArithmeticResponse msg = *wrapped.mutable_arithmetic_response();
        msg.set_result(22.8);
        msg.set_request_id(1);
        this->RaiseEvent(ProtoMessageReceivedEvent::New(nullptr, 0, wrapped));
    };
}

bool SpamGenerator::DoesCareAboutEventType(Event::Type type) const
{
    return type == Event::Type::Tick;
}

void SpamGenerator::OnTick(const TickEvent&)
{
    // We have 8 different event types that we're going to cycle through.
    mEventRaiserDispatchTable[mIterCount++ % 8]();

    if (mIterCount == mMaxIterations)
    {
        LOGF_WARN("Completed max iterations ({}). Shutting down.", mMaxIterations);
        Application::Get().Shutdown(0);
    }
}

bool AllEventConsumer::DoesCareAboutEventType(Event::Type type) const
{
    return type != Event::Type::Tick;
}

void AllEventConsumer::OnTCPClientConnected(const TCPClientConnectedEvent& evt)
{
    mAUselessThingToIncrement += evt.GetSessionId();
}

void AllEventConsumer::OnTCPClientDisconnected(const TCPClientDisconnectedEvent& evt)
{
    mAUselessThingToIncrement += evt.GetSessionId();
}

void AllEventConsumer::OnTCPServerConnected(const TCPServerConnectedEvent& evt)
{
    mAUselessThingToIncrement += evt.GetSessionId();
}

void AllEventConsumer::OnTCPServerDisconnected(const TCPServerDisconnectedEvent& evt)
{
    mAUselessThingToIncrement += evt.GetSessionId();
}

void AllEventConsumer::On_demoproto_NumericMessage(const ProtoMessageReceivedEvent& evt, const demoproto::NumericMessage& msg)
{
    mAUselessThingToIncrement += evt.GetSessionId();
}

void AllEventConsumer::On_demoproto_TextualMessage(const ProtoMessageReceivedEvent& evt, const demoproto::TextualMessage& msg)
{
    mAUselessThingToIncrement += evt.GetSessionId();
}

void AllEventConsumer::On_mathproto_ArithmeticRequest(const ProtoMessageReceivedEvent& evt, const mathproto::ArithmeticRequest& msg)
{
    mAUselessThingToIncrement += evt.GetSessionId();
}

void AllEventConsumer::On_mathproto_ArithmeticResponse(const ProtoMessageReceivedEvent& evt, const mathproto::ArithmeticResponse& msg)
{
    mAUselessThingToIncrement += evt.GetSessionId();
}