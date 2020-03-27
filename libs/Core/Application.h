#pragma once

#ifndef _WIN32
	#error "Project currently only supports Windows, sorry."
#endif

#include "Event.h"

int main(int argc, char* argv[]);

namespace EventCore {

	// The Application class owns the Events from when they are raised 
	// (via the EventQueue instance). They are freed after the OnEvent callback loop.
	class Application
	{
		friend class EntryPoint;

	public:
		virtual ~Application();
		void Shutdown(int exitCode = 0);
		
		static Application& Get() { return *sInstance; }
		inline bool IsRunning() const { return mIsRunning; }

		// Whatever creates the EventProducer is responsible for 
		// the lifetime of that event producer, including ensuring it is
		// removed / unregistered from here before the memory is freed.
		// Otherwise we'll keep trying to call on them during the
		// Event Queue's OnUpdate callbacks.
		void RegisterEventProducer(EventProducer*);
		void UnregisterEventProducer(EventProducer*);

		// As above.
		void RegisterEventConsumer(EventConsumer*);
		void UnregisterEventConsumer(EventConsumer*);
		
		EventQueue& GetEventQueue() { return mEventQueue; }

	private:
		static Application* sInstance;
		
		virtual void Init() = 0;
		virtual void OnUpdate() = 0;

		void Run();

		bool mIsRunning{true};
		int mExitCode{0};

		// The EventQueue takes ownership of the Events when they are raised.
		EventQueue mEventQueue;
		// The Application base class does not own these event producers.
		std::vector<EventProducer*> mEventProducers;
	};

	// Application must be subclassed by an app that uses this class, 
	// and it must implement this function to return the application instance.
	Application* CreateApplication();

	class EntryPoint
	{
	public:
		static int MainFunction(int argc, char* argv[]);
	};
	
}