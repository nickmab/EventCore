// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoClient.h"

#include <iostream>

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::DemoClient();
	}
}

using namespace EventCore;

void DemoClient::Init()
{
	if (!mTCPClient.Init())
	{
		std::cout << "Could not initialize client; shutting down." << std::endl;
		Shutdown(1);
	}
}

void DemoClient::OnUpdate()
{
	// temporary crappy hack...
	if (!mTCPClient.OnUpdate())
	{
		std::cout << "Encountered some kind of error; shutting down." << std::endl;
		Shutdown(1);
	}
}