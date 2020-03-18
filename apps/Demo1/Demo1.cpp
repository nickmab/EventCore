// EventCore.cpp : Defines the entry point for the application.
//

#include "Demo1.h"

#include "Core/Events/Utility/OnTickProducer.h"
#include "Core/Events/Utility//EventPrinter.h"

#include <iostream>

namespace EventCore {
	Application* CreateApplication()
	{
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
		std::cout << "DemoApp has decided it's time to shutdown." << std::endl;
		Shutdown();
	}
}