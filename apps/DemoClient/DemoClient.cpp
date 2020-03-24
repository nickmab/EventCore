// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoClient.h"
#include "Core/Logger.h"

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::DemoClient(DemoProtoParser::New());
	}
}

using namespace EventCore;

DemoClient::DemoClient(ProtoParser* parser)
	: mTCPClient(parser)
{
}

void DemoClient::Init()
{
	if (!mTCPClient.Init())
	{
		LOG_CRITICAL("Could not initialize client; shutting down.");
		Shutdown(1);
	}
}

void DemoClient::OnUpdate()
{
	// temporary crappy hack...
	if (!mTCPClient.OnUpdate())
	{
		LOG_CRITICAL("Encountered some kind of error; shutting down.");
		Shutdown(1);
	}
}