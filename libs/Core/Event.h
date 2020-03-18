#pragma once

#include <string>
#include <functional>
#include <memory>
#include <vector>

namespace EventCore {

	class Event
	{
	public:

		enum class Type
		{
			Null = 0,
			OnTick
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
		std::vector<std::shared_ptr<EventConsumer> > mConsumers;
	};

}