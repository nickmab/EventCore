// EventCore.cpp : Defines the entry point for the application.
//

#include "Demo1.h"

EventCore::Application* EventCore::CreateApplication()
{
	return new DemoApp();
}

void DemoApp::OnUpdate()
{
	std::cout << mSomeInteger++ << std::endl;
	if (mSomeInteger > 9)
		Shutdown();
}