#include "pch.h"

#include "Event.h"
#include "Application.h"

#include "Events/TickEvent.h"
#include "Proto/ProtoEvents.h"
#include "TCP/TCPEvents.h"

namespace EventCore {

    Event::Event(const EventProducer* sender)
        : mSender(sender)
    {}
    
    EventProducer::EventProducer(EventCallbackFn callback)
        : mCallback(callback)
    {}

    std::string EventProducer::ToString() const
    {
        std::stringstream ss;
        ss << "Unnamed EventProducer at " << this;
        return ss.str();
    }
    
    void EventProducer::RaiseEvent(Event* evt) const
    {
        if (mCallback)
            mCallback(evt);
        else
        {
            Application::Get().GetEventQueue().EnqueueEvent(evt);
        }
    }

    bool EventConsumer::DoesCareAboutEventType(Event::Type type) const
    {
        return mEventsCaredAbout.find(type) != mEventsCaredAbout.end();
    }

    void EventConsumer::OnEvent(const Event& evt)
    {
        TIME_SCOPE;

        const Event::Type type = evt.GetType();

#define TYPE_SWITCH(evt_type) \
    case Event::Type:: ## evt_type: \
        { InstrumentationTimer timer("On" #evt_type); \
        On ## evt_type ## (reinterpret_cast<const evt_type ## Event&>(evt)); } \
        break;

            switch (type)
            {
                TYPE_SWITCH(Tick)
                TYPE_SWITCH(TCPConnection)
                TYPE_SWITCH(ProtoMessageReceived)
            default:
                ASSERTF(false, "This should be unreachable; unhandled event type: {}", type);
            }
#undef TYPE_SWITCH
    }

    void EventConsumer::OnProtoMessageReceived(const ProtoMessageReceivedEvent& evt)
    {
        TIME_SCOPE;

        const ProtoMsgVariant& msg = evt.GetMessage();
        if (std::holds_alternative<demoproto::WrappedMessage>(msg))
        {
            auto wrapped = std::get<demoproto::WrappedMessage>(msg);
            if (wrapped.has_numeric_message())
            {
                On_demoproto_NumericMessage(evt, wrapped.numeric_message());
            }
            else if (wrapped.has_textual_message())
            {
                On_demoproto_TextualMessage(evt, wrapped.textual_message());
            }
            else
            {
                LOG_CRITICAL("Unrecognized message type in demoproto::WrappedMessage!");
                Application::Get().Shutdown(1);
            }
        }
        else if (std::holds_alternative<mathproto::WrappedMessage>(msg))
        {
            auto wrapped = std::get<mathproto::WrappedMessage>(msg);
            if (wrapped.has_arithmetic_request())
            {
                On_mathproto_ArithmeticRequest(evt, wrapped.arithmetic_request());
            }
            else if (wrapped.has_arithmetic_response())
            {
                On_mathproto_ArithmeticResponse(evt, wrapped.arithmetic_response());
            }
            else
            {
                LOG_CRITICAL("Unrecognized message type in mathproto::WrappedMessage!");
                Application::Get().Shutdown(1);
            }
        }
        else
        {
            LOG_CRITICAL("This function must be called with a Wrapped message type!");
            Application::Get().Shutdown(1);
        }
    }

    void EventQueue::RegisterConsumer(EventConsumer* consumer)
    {
        for (int i = 1; i < static_cast<int>(Event::Type::End); i++)
        {
            Event::Type eventType = static_cast<Event::Type>(i);
            if (consumer->DoesCareAboutEventType(eventType))
                mEventTypeToConsumerMap[eventType].push_back(consumer);
        }
    }

    void EventQueue::UnregisterConsumer(EventConsumer* consumer)
    {
        // should check that this actually works...
        for (int i = 1; i < static_cast<int>(Event::Type::End); i++)
        {
            Event::Type eventType = static_cast<Event::Type>(i);
            if (consumer->DoesCareAboutEventType(eventType))
            {
                auto vec = mEventTypeToConsumerMap[eventType];
                auto it = std::find(vec.begin(), vec.end(), consumer);
                if (it != vec.end())
                    vec.erase(it);
            }
        }
    }

    void EventQueue::EnqueueEvent(Event* evtPtr)
    {
        mEventQueue.emplace_back(evtPtr);
    }

    void EventQueue::PublishEvents()
    {
        int eventsProcessed = 0;
        for (auto& evt : mEventQueue)
        {
            eventsProcessed++;
            auto consumerVec = mEventTypeToConsumerMap[evt->GetType()];

            for (auto* consumer : consumerVec)
            {
                if (!Application::Get().IsRunning())
                    break;
                consumer->OnEvent(*evt);
            }
        }

        // We have to do this because if any of the consumers themselves _also_ raise
        // events during their callbacks, they wil be added to the back of the queue
        // but _not_ processed during the above for loop. Thus we cannot
        // trivially clear the event queue at this point. 
        mEventQueue.erase(mEventQueue.begin(), mEventQueue.begin() + eventsProcessed);
    }

}