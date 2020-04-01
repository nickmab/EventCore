#include <pch.h>

#include "EventProfiler.h"

#include <tclap/CmdLine.h>

auto EventProfiler::ParseArgs(int argc, char* argv[])
{
    struct returnStruct { int mLoopsToRun, mLoopEveryNMillis; };
    int loopsToRun{0}, loopEveryNMillis{0};
    try
    {
        TCLAP::CmdLine cmd("Event profiler", ' ', "0.1");

        // filename arg; required, no default value.
        TCLAP::ValueArg<int> loopFrequencyArg("f", "frequency", 
            "Raise an event every 'f' millis.", true, 0, "frequency:int");

        TCLAP::ValueArg<int> loopCountArg("l", "loops",
            "Raise a total of 'l' events before exiting.", true, 0, "loops:int");

        cmd.add(loopFrequencyArg);
        cmd.add(loopCountArg);
        cmd.parse(argc, argv);

        loopsToRun = loopCountArg.getValue();
        loopEveryNMillis = loopFrequencyArg.getValue();
    }
    catch (TCLAP::ArgException & e)
    {
        LOGF_CRITICAL("Error parsing cmd line args. Error: {} Argument: {}",
            e.error(), e.argId());
    }

    return returnStruct{ loopsToRun, loopEveryNMillis };
}

namespace EventCore {
    Application* CreateApplication(int argc, char* argv[])
    {
        auto [loopsToRun, loopEveryNMillis] = ::EventProfiler::ParseArgs(argc, argv);
        if (loopsToRun <= 0 || loopEveryNMillis <= 0)
        {
            LOGF_CRITICAL("Both command line args must be >0. Got loopsToRun {} and loopEveryNMillis {}.",
                loopsToRun, loopEveryNMillis);
            return nullptr;
        }
        return new ::EventProfiler(loopsToRun, loopEveryNMillis);
    }
}

using namespace EventCore;

EventProfiler::EventProfiler(int totalLoopsToRun, int loopEveryNMillis)
    : mTotalLoopsToRun(totalLoopsToRun)
    , mLoopEveryNMillis(loopEveryNMillis)
{
}

void EventProfiler::Init()
{
    mTickEventProducer.reset(new TickEventProducer(mLoopEveryNMillis));
    RegisterEventProducer(mTickEventProducer.get());

    mSpamGenerator.reset(new SpamGenerator(mTotalLoopsToRun));
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
    mEventRaiserDispatchTable[0] = [this]() { 
        InstrumentationTimer t("RaiseTCPConnectionEvent");
        this->RaiseEvent(new TCPConnectionEvent(nullptr, 0, TCPConnectionEvent::Type::ClientConnected)); 
    };
    mEventRaiserDispatchTable[1] = [this]() { 
        InstrumentationTimer t("RaiseNumericMessageEvent");
        demoproto::WrappedMessage wrapped;
        demoproto::NumericMessage& msg = *wrapped.mutable_numeric_message();
        msg.set_a_double(9.0);
        msg.set_an_integer(3);
        this->RaiseEvent(ProtoMessageReceivedEvent::New(nullptr, 0, wrapped)); 
    };
    mEventRaiserDispatchTable[2] = [this]() {
        InstrumentationTimer t("RaiseTextualMessageEvent");
        demoproto::WrappedMessage wrapped;
        demoproto::TextualMessage& msg = *wrapped.mutable_textual_message();
        msg.set_a_sentence("Hello, world");
        msg.set_is_interesting(true);
        this->RaiseEvent(ProtoMessageReceivedEvent::New(nullptr, 0, wrapped));
    };
    mEventRaiserDispatchTable[3] = [this]() {
        InstrumentationTimer t("RaiseArithmeticRequestEvent");
        mathproto::WrappedMessage wrapped;
        mathproto::ArithmeticRequest msg = *wrapped.mutable_arithmetic_request();
        msg.set_lhs(3.0);
        msg.set_op(mathproto::ArithmeticOperator::TIMES);
        msg.set_rhs(7.6);
        msg.set_request_id(1);
        this->RaiseEvent(ProtoMessageReceivedEvent::New(nullptr, 0, wrapped));
    };
    mEventRaiserDispatchTable[4] = [this]() {
        InstrumentationTimer t("RaiseArithmeticResponseEvent");
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
    auto fn = mEventRaiserDispatchTable[mIterCount++ % 5];
    { InstrumentationTimer timer("FnCall");
        // We have 5 different event types that we're going to cycle through.
        fn();
    }
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

void AllEventConsumer::OnTCPConnection(const TCPConnectionEvent& evt)
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