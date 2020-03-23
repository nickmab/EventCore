// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoServer.h"

#include "Core/Events/Utility/OnTickProducer.h"
#include "Core/Events/Utility/EventPrinter.h"
#include "Core/Logger.h"

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::DemoServer();
	}
}

using namespace EventCore;

void DemoServer::Init()
{
	OnTickProducer* producer = new OnTickProducer(
		std::bind(&EventQueue::EnqueueEvent, &GetEventQueue(), std::placeholders::_1),
		1000);
	
	RegisterEventProducer(std::shared_ptr<EventProducer>(producer));

	EventPrinter* consumer = new EventPrinter();
	GetEventQueue().RegisterConsumer(std::shared_ptr<EventConsumer>(consumer));

	if (!mServer.Init())
	{
		LOG_CRITICAL("Could not initialize server; shutting down.");
		Shutdown(1);
	}
}

void DemoServer::OnUpdate()
{
	if (!mServer.OnUpdate())
	{
		LOG_CRITICAL("Encountered some kind of error in server; shutting down.");
		Shutdown(1);
	}
}