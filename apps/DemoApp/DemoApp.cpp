// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoApp.h"

#include "Core/Events/Utility/OnTickProducer.h"
#include "Core/Events/Utility/EventPrinter.h"
#include "Core/Logger.h"

#include <Proto/DemoProto/DemoProto.pb.h>
#include <iostream>

namespace EventCore {
	Application* CreateApplication()
	{
		demoproto::Example e;
		e.set_anumber(6123);
		std::cout << e.anumber() << std::endl;
		return new ::DemoApp(7);
	}
}

using namespace EventCore;

DemoApp::DemoApp(double secondsToStayAlive)
	: mSecondsToStayAlive(secondsToStayAlive)
	, mApplicationStartTime(std::chrono::system_clock::now())
{}

void DemoApp::Init()
{
	OnTickProducer* producer = new OnTickProducer(
		std::bind(&EventQueue::EnqueueEvent, &GetEventQueue(), std::placeholders::_1),
		1000);
	
	RegisterEventProducer(std::shared_ptr<EventProducer>(producer));

	EventPrinter* consumer = new EventPrinter();
	GetEventQueue().RegisterConsumer(std::shared_ptr<EventConsumer>(consumer));
}

void DemoApp::OnUpdate()
{
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<double> secondsAlive = now - mApplicationStartTime;

	if (secondsAlive.count() > mSecondsToStayAlive) 
	{
		LOG_WARN("DemoApp has decided it's time to shutdown.");
		Shutdown();
	}
}