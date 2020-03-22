#include "Application.h"

#include <string>
#include <iostream>
#include "Proto/DemoProto/DemoProto.pb.h"

int main(int argc, char* argv[])
{
	demoproto::NumericMessage msg;
	msg.set_an_integer(6123);
	msg.set_a_double(42.1);
	std::cout << msg.DebugString() << std::endl;
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

	void Application::RegisterEventProducer(std::shared_ptr<EventProducer> producer)
	{
		mEventProducers.push_back(producer);
	}

	void Application::UnregisterEventProducer(std::shared_ptr<EventProducer> producer)
	{
		// should check that this actually works...
		auto it = std::find(mEventProducers.begin(), mEventProducers.end(), producer);
		if (it != mEventProducers.end())
			mEventProducers.erase(it);
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

			for (std::shared_ptr<EventProducer> producer : mEventProducers)
			{
				if (mIsRunning)
				{
					producer->OnUpdate();
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