#include "Application.h"

#include "Event.h"

int main(int argc, char* argv[])
{
	return EventCore::EntryPoint::MainFunction(argc, argv);
}

namespace EventCore {

	// see declaration of extern static Application* CreateApplication(); in Application.h
	Application* Application::sInstance = nullptr;

	Application::~Application()
	{
	}

	void Application::Shutdown(int exitCode)
	{
		mExitCode = exitCode; 
		mIsRunning = false;
	}

	void Application::RegisterEventProducer(EventProducer* producer)
	{
		mEventProducers.push_back(producer);
	}

	void Application::UnregisterEventProducer(EventProducer* producer)
	{
		// should check that this actually works...
		auto it = std::find(mEventProducers.begin(), mEventProducers.end(), producer);
		if (it != mEventProducers.end())
			mEventProducers.erase(it);
	}

	void Application::RegisterEventConsumer(EventConsumer* consumer)
	{
		mEventQueue.RegisterConsumer(consumer);
	}

	void Application::UnregisterEventConsumer(EventConsumer* consumer)
	{
		mEventQueue.UnregisterConsumer(consumer);
	}

	void Application::Run()
	{
		for (;;)
		{
			if (mIsRunning)
			{
				OnUpdate();
			}
			else
			{
				return;
			}

			for (auto* producer : mEventProducers)
			{
				if (mIsRunning)
				{
					producer->EventProducerOnUpdate();
				}
				else
				{
					return;
				}
			}

			if (mIsRunning)
			{
				mEventQueue.PublishEvents();
			}
			else
			{
				return;
			}
		}
			
	}

	int EntryPoint::MainFunction(int argc, char* argv[])
	{
		Application* instance = CreateApplication();
		Application::sInstance = instance;
		instance->Init();
		instance->Run();
		int exitCode = instance->mExitCode;
		delete instance;
		return exitCode;
	}
		
}