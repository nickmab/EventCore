#include "Event.h"
#include "Application.h"

namespace EventCore {

	EventProducer::EventProducer(EventCallbackFn callback)
		: mCallback(callback)
	{}

	void EventProducer::OnUpdate()
	{
		Event* evtPtr = OnUpdateImpl();
		if (evtPtr)
			mCallback(evtPtr);
	}

	Event* EventProducer::OnUpdateImpl()
	{
		return nullptr;
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