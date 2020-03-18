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
		mConsumers.push_back(consumer);
	}

	void EventQueue::UnregisterConsumer(std::shared_ptr<EventConsumer> consumer)
	{
		// should check that this actually works...
		auto it = std::find(mConsumers.begin(), mConsumers.end(), consumer);
		if (it != mConsumers.end())
			mConsumers.erase(it);
	}

	void EventQueue::EnqueueEvent(std::shared_ptr<Event> evtPtr)
	{
		mEventQueue.push_back(evtPtr);
	}

	void EventQueue::PublishEvents()
	{
		for (std::shared_ptr<Event> evtPtr : mEventQueue)
		{
			for (std::shared_ptr<EventConsumer> consumer : mConsumers)
			{
				if (!Application::Get().IsRunning())
					break;
				
				if (consumer->DoesCareAboutEventType(evtPtr->GetType()))
					consumer->OnEvent(*evtPtr);
			}
		}

		mEventQueue.clear();
	}

}