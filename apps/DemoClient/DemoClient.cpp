// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoClient.h"

#include <Core/Logger.h>
#include <Proto/ProtoParser.h>

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::DemoClient();
	}
}

using namespace EventCore;

void DemoClient::Init()
{
	mEventPrinter.reset(new EventPrinter());
	RegisterEventConsumer(mEventPrinter.get());

	mTCPClient.reset(new TCPClient(ProtoParser::Protocol::DemoProto));
	RegisterEventProducer(mTCPClient.get());
	
	if (!mTCPClient->Init())
	{
		LOG_CRITICAL("Could not initialize client; shutting down.");
		Shutdown(1);
	}
}

void DemoClient::OnUpdate()
{	
	if (!mTCPClient->OnUpdate())
	{
		LOG_CRITICAL("Encountered some kind of error; shutting down.");
		Shutdown(1);
	}
}