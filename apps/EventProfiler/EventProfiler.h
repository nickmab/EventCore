#pragma once

#include <Core/Application.h>

#include <Core/Events/EventQueue.h>
#include <Core/Events/Utility/TickEventProducer.h>

using namespace EventCore;

// forward decs of the below classes
class SpamGenerator;
class AllEventConsumer;

class EventProfiler: public Application
{
public:
    static auto EventProfiler::ParseArgs(int argc, char* argv[]);
    
    EventProfiler(int totalLoopsToRun, int loopEveryNMillis);

private:
    virtual void Init() override;
    virtual void OnUpdate() override;

    const int mTotalLoopsToRun; 
    const int mLoopEveryNMillis;

    std::unique_ptr<TickEventProducer> mTickEventProducer;
    std::unique_ptr<SpamGenerator> mSpamGenerator;
    std::unique_ptr<AllEventConsumer> mAllEventConsumer;
};

// This thing will listen to OnTick events and, on tick, randomly generate 
class SpamGenerator
    : public EventProducer
    , public EventConsumer
{
public:
    SpamGenerator(unsigned maxIterations);
    
    // Only OnTick events.
    virtual bool DoesCareAboutEventType(Event::Type) const override;

private:
    const unsigned mMaxIterations;
    unsigned mIterCount{0};

    // Each OnTick callback, we will raise an event by calling one
    // of these lambda functions (defined in the constructor). That
    // way we can easily cycle through which event we call using a simple
    // counter (e.g. call the function at index [count % 5]).
    using EventRaiserFn = std::function<void(void)>;
    EventRaiserFn mEventRaiserDispatchTable[5];

    virtual void OnTick(const TickEvent&) override;
};

// The idea is we listen to all event types and do something trivial
// with them just for the sake of exercising the full virtual 
// polymorphic callback thingy. 
class AllEventConsumer : public EventConsumer
{
public:
    // ...everything _except_ OnTick events.
    virtual bool DoesCareAboutEventType(Event::Type) const override;

private:
    unsigned long mAUselessThingToIncrement{0};

    virtual void OnTCPConnection(const TCPConnectionEvent&) override;

    virtual void On_demoproto_NumericMessage(const ProtoMessageReceivedEvent&, const demoproto::NumericMessage&) override;
    virtual void On_demoproto_TextualMessage(const ProtoMessageReceivedEvent&, const demoproto::TextualMessage&) override;
    virtual void On_mathproto_ArithmeticRequest(const ProtoMessageReceivedEvent&, const mathproto::ArithmeticRequest&) override;
    virtual void On_mathproto_ArithmeticResponse(const ProtoMessageReceivedEvent&, const mathproto::ArithmeticResponse&) override;
};

Application* CreateApplication(int argc, char* argv[]);