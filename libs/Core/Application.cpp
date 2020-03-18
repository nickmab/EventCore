#include "Application.h"

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

	void Application::Run()
	{
		while (mIsRunning)
			OnUpdate();
	}

	int EntryPoint::MainFunction(int argc, char* argv[])
	{
		Application* instance = CreateApplication();
		Application::sInstance = instance;
		instance->Run();
		int exitCode = instance->mExitCode;
		delete instance;
		return exitCode;
	}
		
}