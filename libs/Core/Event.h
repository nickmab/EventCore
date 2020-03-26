#pragma once

#include <functional>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

// Forward decs of message types.
namespace demoproto {
	class NumericMessage;
	class TextualMessage;
}

namespace EventCore {

	// Forward decs of event types
	class TickEvent;
	class TCPClientConnectedEvent;
	class TCPClientDisconnectedEvent;
	class TCPServerConnectedEvent;
	class TCPServerDisconnectedEvent;
	class ProtoMessageReceivedEvent;

	// another forward dec for later in this file.
	class EventProducer;

	class Event
	{
	public:

		Event(const EventProducer* sender);

		// ALL events MUST be added to this enum.
		enum class Type
		{
			Begin = 0,
			
			// Insert events in here. "Begin" and "End" are used just for iteration.
			Tick,
			TCPClientConnected,
			TCPClientDisconnected,
			TCPServerConnected,
			TCPServerDisconnected,
			ProtoMessageReceived,
			
			// Insert events in the section above. "Begin" and "End" are used just for iteration.
			End
		};

		inline virtual Event::Type GetType() const = 0;
		inline virtual const char* const GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline const EventProducer* GetSender() const { return mSender; }

	private:
		const EventProducer* mSender;
	};

	class EventProducer
	{
	public:
		using EventCallbackFn = std::function<void(Event*)>;

		// specify callback function (e.g. Application::OnEvent) to forward events
		// to when we instantiate the producer. If left as null, will use default.
		EventProducer(EventCallbackFn fn = nullptr);
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
		EventCallbackFn mCallback;
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
		virtual void OnTCPClientConnected(const TCPClientConnectedEvent&) {}
		virtual void OnTCPClientDisconnected(const TCPClientDisconnectedEvent&) {}
		virtual void OnTCPServerConnected(const TCPServerConnectedEvent&) {}
		virtual void OnTCPServerDisconnected(const TCPServerDisconnectedEvent&) {}
		
		virtual void OnProtoMessageReceived(const ProtoMessageReceivedEvent&);
		virtual void On_demoproto_NumericMessage(const ProtoMessageReceivedEvent&, const demoproto::NumericMessage&) {}
		virtual void On_demoproto_TextualMessage(const ProtoMessageReceivedEvent&, const demoproto::TextualMessage&) {}
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