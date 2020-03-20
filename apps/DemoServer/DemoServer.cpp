// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoServer.h"

#include "Core/Events/Utility/OnTickProducer.h"
#include "Core/Events/Utility/EventPrinter.h"
#include "Core/Logger.h"

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::DemoServer(10);
	}
}

using namespace EventCore;

DemoServer::DemoServer(double secondsToStayAlive)
	: mSecondsToStayAlive(secondsToStayAlive)
	, mApplicationStartTime(std::chrono::system_clock::now())
{}

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
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<double> secondsAlive = now - mApplicationStartTime;

	if (secondsAlive.count() > mSecondsToStayAlive) 
	{
		LOGF_WARN("The server has decided it's time to shutdown after {} seconds. Bad luck, son.", mSecondsToStayAlive);
		Shutdown();
	}

	// temporary crappy hack...
	if (!mServer.OnUpdate())
	{
		LOG_CRITICAL("Encountered some kind of error in server; shutting down.");
		Shutdown(1);
	}
}