#include "Event.h"
#include "Application.h"

namespace EventCore {

	EventProducer::EventProducer(EventCallbackFn callback)
		: mCallback(callback)
	{}

	void EventProducer::OnUpdate()
	{
		std::shared_ptr<Event> evtPtr = OnUpdateImpl();
		if (evtPtr)
			mCallback(evtPtr);
	}

	void EventQueue::RegisterConsumer(std::shared_ptr<EventConsumer> consumer)
	{
		for (int i = 1; i < static_cast<int>(Event::Type::End); i++)
		{
			Event::Type eventType = static_cast<Event::Type>(i);
			if (consumer->DoesCareAboutEventType(eventType))
				mEventTypeToConsumerMap[eventType].push_back(consumer);
		}
	}

	void EventQueue::UnregisterConsumer(std::shared_ptr<EventConsumer> consumer)
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

	void EventQueue::EnqueueEvent(std::shared_ptr<Event> evtPtr)
	{
		mEventQueue.push_back(evtPtr);
	}

	void EventQueue::PublishEvents()
	{
		for (std::shared_ptr<Event> evtPtr : mEventQueue)
		{
			auto consumerVec = mEventTypeToConsumerMap[evtPtr->GetType()];
			for (std::shared_ptr<EventConsumer> consumer : consumerVec)
			{
				if (!Application::Get().IsRunning())
					break;
				consumer->OnEvent(*evtPtr);
			}
		}

		mEventQueue.clear();
	}

}