#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace EventCore {

	class Event
	{
	public:

		// ALL events MUST be added to this enum.
		enum class Type
		{
			Begin = 0,
			
			// Insert events in here. "Begin" and "End" are used just for iteration.
			OnTick,
			TCPClientConnected,
			TCPClientDisconnected,
			TCPServerConnected,
			TCPServerDisconnected,
			OnProtoMessageReceived,
			
			// Insert events in the section above. "Begin" and "End" are used just for iteration.
			End
		};

		inline virtual Event::Type GetType() const = 0;
		inline virtual const char* const GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

	class EventProducer
	{
	public:
		using EventCallbackFn = std::function<void(Event*)>;
		
		// specify callback function (e.g. Application::OnEvent) to forward events
		// to when we instantiate the producer.
		EventProducer(EventCallbackFn);
		virtual ~EventProducer() = default;
		
		// will be periodically called (and calls OnUpdateImpl under the hood) every run loop
		// giving the chance for the producer to raise an event.
		// However, it can also raise an event any time it wants just by calling the callback fn.
		void OnUpdate();

	protected:
		EventCallbackFn mCallback;

	private:
		// Subclass should "new" a concrete event type and give it back to us. 
		// The ownership will be transferred to the EventQueue object at the Application level.
		// Should return nullptr if no event needs to be raised/produced.
		virtual Event* OnUpdateImpl();
	};

	class EventConsumer
	{
	public:
		virtual ~EventConsumer() = default;
		virtual bool DoesCareAboutEventType(Event::Type) const = 0;
		virtual void OnEvent(const Event&) = 0;
	};

	// Takes ownership of the lifetime of the Event instances.
	class EventQueue
	{
	public:
		// Whatever creates the EventConsumeris responsible for 
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