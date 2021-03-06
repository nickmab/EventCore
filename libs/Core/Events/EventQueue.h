#pragma once

#include "TickEvent.h"
#include "Proto/ProtoEvents.h"
#include "TCP/TCPEvents.h"
#include "TCP/TCPSession.h"

namespace EventCore {

    class EventProducer
    {
    public:
        virtual ~EventProducer() {}
        
        // will be periodically called every run loop
        // giving the chance for the producer to raise an event.
        // However, it can also raise an event any time it wants just by calling the RaiseEvent(Event*) function.
        virtual void EventProducerOnUpdate() {}

        virtual std::string ToString() const;

    protected:
        // Subclass should "new" a concrete event type and raise by calling this function.
        // The ownership will be transferred to the EventQueue object at the Application level.
        // Should return nullptr if no event needs to be raised/produced.
        void RaiseEvent(Event*) const;
    };

    class EventConsumer
    {
    public:
        EventConsumer() {}
        virtual ~EventConsumer() {}
        
        virtual bool DoesCareAboutEventType(Event::Type) const;
        
        virtual void OnEvent(const Event&);

    protected:
        std::set<Event::Type> mEventsCaredAbout;

    private:
        virtual void OnTick(const TickEvent&) {}
        virtual void OnTCPConnection(const TCPConnectionEvent&) {}
        
        virtual void OnProtoMessageReceived(const ProtoMessageReceivedEvent&);
        virtual void On_demoproto_NumericMessage(const ProtoMessageReceivedEvent&, const demoproto::NumericMessage&) {}
        virtual void On_demoproto_TextualMessage(const ProtoMessageReceivedEvent&, const demoproto::TextualMessage&) {}
        virtual void On_mathproto_ArithmeticRequest(const ProtoMessageReceivedEvent&, const mathproto::ArithmeticRequest&) {}
        virtual void On_mathproto_ArithmeticResponse(const ProtoMessageReceivedEvent&, const mathproto::ArithmeticResponse&) {}
    };

    // Takes ownership of the lifetime of the Event instances.
    class EventQueue
    {
        friend class EventProducer;

    public:
        // Whatever creates the EventConsumer is responsible for 
        // the lifetime of that event consumer, including ensuring it is
        // removed / unregistered from here before the memory is freed.
        // Otherwise we'll keep trying to call on them during the
        // OnEvent callbacks.
        void RegisterConsumer(EventConsumer*);
        void UnregisterConsumer(EventConsumer*);

        // WE TAKE OWNERSHIP of the Event here.
        void EnqueueEvent(Event*);
        // WE FREE the Event after this callback.
        void PublishEvents();

    private:
        std::vector<std::unique_ptr<Event> > mEventQueue;
        
        // For each event type, we keep a vector of shared_ptrs to consumers that 
        // are interested in consuming that event type. Used for convenient/efficient
        // callback when we actually publish events / empty the queue. 
        // Thus a consumer that listens for multiple event types will appear multiple
        // times in this map.
        std::map<Event::Type, std::vector<EventConsumer*> > mEventTypeToConsumerMap;
    };

}