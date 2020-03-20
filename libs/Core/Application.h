#pragma once

#include "Event.h"
#include "Logger.h"

int main(int argc, char* argv[]);

namespace EventCore {

	class Application
	{
		friend class EntryPoint;

	public:
		virtual ~Application();
		void Shutdown(int exitCode = 0);
		
		static Application& Get() { return *sInstance; }
		inline bool IsRunning() const { return mIsRunning; }

	protected:
		void RegisterEventProducer(std::shared_ptr<EventProducer>);
		void UnregisterEventProducer(std::shared_ptr<EventProducer>);
		EventQueue& GetEventQueue() { return mEventQueue; }

	private:
		static Application* sInstance;
		
		virtual void Init() = 0;
		virtual void OnUpdate() = 0;

		void Run();

		bool mIsRunning{ true };
		int mExitCode{0};

		EventQueue mEventQueue;
		std::vector<std::shared_ptr<EventProducer> > mEventProducers;
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