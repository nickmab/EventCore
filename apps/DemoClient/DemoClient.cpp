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

void DemoClient::Init()
{
	mEventPrinter.reset(new EventPrinter());
	GetEventQueue().RegisterConsumer(mEventPrinter.get());

	mProtoParser.reset(new DemoProtoParser(
		std::bind(&EventQueue::EnqueueEvent, &GetEventQueue(), std::placeholders::_1)));

	RegisterEventProducer(mProtoParser.get());

	mTCPClient.reset(new TCPClient(
		std::bind(&EventQueue::EnqueueEvent, &GetEventQueue(), std::placeholders::_1),
		mProtoParser.get()));
	
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