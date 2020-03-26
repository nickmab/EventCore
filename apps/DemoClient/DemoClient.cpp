// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoClient.h"

#include <Core/Logger.h>

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::DemoClient();
	}
}

using namespace EventCore;

ProtoParser* DemoClient::NewProtoParser()
{
	// This function lives here so we can bind it to the correct event production callback. 
	// I don't fully love this pattern, it might change.
	return new DemoProtoParser();
}

void DemoClient::Init()
{
	mEventPrinter.reset(new EventPrinter());
	GetEventQueue().RegisterConsumer(mEventPrinter.get());

	mProtoParser.reset(new DemoProtoParser());

	RegisterEventProducer(mProtoParser.get());

	mTCPClient.reset(new TCPClient(std::bind(&DemoClient::NewProtoParser, this)));
	
	if (!mTCPClient->Init())
	{
		LOG_CRITICAL("Could not initialize client; shutting down.");
		Shutdown(1);
	}
}

void DemoClient::OnUpdate()
{	
	// temporary crappy hack...
	if (!mTCPClient->OnUpdate())
	{
		LOG_CRITICAL("Encountered some kind of error; shutting down.");
		Shutdown(1);
	}
}