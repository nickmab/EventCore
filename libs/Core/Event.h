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
			OnDemoProtoMessage,
			
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
		using EventCallbackFn = std::function<void(std::shared_ptr<Event>)>;
		
		// specify callback function (e.g. Application::OnEvent) to forward events
		// to when we instantiate the producer.
		EventProducer(EventCallbackFn);
		virtual ~EventProducer() = default;
		
		void OnUpdate();

	private:
		// client should return nullptr if no event needs to be raised/produced.
		virtual std::shared_ptr<Event> OnUpdateImpl() = 0;
		
		EventCallbackFn mCallback;
	};

	class EventConsumer
	{
	public:
		virtual ~EventConsumer() = default;
		virtual bool DoesCareAboutEventType(Event::Type) const = 0;
		virtual void OnEvent(const Event&) = 0;
	};

	class EventQueue
	{
	public:
		void RegisterConsumer(std::shared_ptr<EventConsumer>);
		void UnregisterConsumer(std::shared_ptr<EventConsumer>);

		void EnqueueEvent(std::shared_ptr<Event>);
		void PublishEvents();

	private:
		std::vector<std::shared_ptr<Event> > mEventQueue;
		
		// For each event type, we keep a vector of shared_ptrs to consumers that 
		// are interested in consuming that event type. Used for convenient/efficient
		// callback when we actually publish events / empty the queue. 
		// Thus a consumer that listens for multiple event types will appear multiple
		// times in this map.
		std::map<Event::Type, std::vector<std::shared_ptr<EventConsumer> > > mEventTypeToConsumerMap;
	};

}