#include "Event.h"
#include "Application.h"

#include "Events/TickEvent.h"
#include "Proto/ProtoEvents.h"
#include "TCP/TCPEvents.h"

#include <sstream>

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
		mCallback(evt);
	}

	bool EventConsumer::DoesCareAboutEventType(Event::Type type) const
	{
		return mEventsCaredAbout.find(type) != mEventsCaredAbout.end();
	}

	void EventConsumer::OnEvent(const Event& evt)
	{
		const Event::Type type = evt.GetType();
		if (DoesCareAboutEventType(type))
		{

#define TYPE_SWITCH(evt_type) \
	case Event::Type:: ## evt_type: \
		On ## evt_type ## (reinterpret_cast<const evt_type ## Event&>(evt)); \
		break;

			switch (type)
			{
				TYPE_SWITCH(Tick)
				TYPE_SWITCH(TCPClientConnected)
				TYPE_SWITCH(TCPClientDisconnected)
				TYPE_SWITCH(TCPServerConnected)
				TYPE_SWITCH(TCPServerDisconnected)
				TYPE_SWITCH(ProtoMessageReceived)
			default:
				ASSERTF(false, "This should be unreachable; unhandled event type: {}", type);
			}
		}
#undef TYPE_SWITCH
	}

	void EventConsumer::OnProtoMessageReceived(const ProtoMessageReceivedEvent& evt)
	{
		const ProtoMsgVariant& msg = evt.GetMessage();
		if (std::holds_alternative<demoproto::NumericMessage>(msg))
			On_demoproto_NumericMessage(std::get<demoproto::NumericMessage>(msg));
		else if (std::holds_alternative<demoproto::TextualMessage>(msg))
			On_demoproto_TextualMessage(std::get<demoproto::TextualMessage>(msg));
		else
			ASSERT(false, "This should be unreachable; unrecognised event type.");
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
		for (auto& evt : mEventQueue)
		{
			auto consumerVec = mEventTypeToConsumerMap[evt->GetType()];
			for (auto* consumer : consumerVec)
			{
				if (!Application::Get().IsRunning())
					break;
				consumer->OnEvent(*evt);
			}
		}

		mEventQueue.clear();
	}

}