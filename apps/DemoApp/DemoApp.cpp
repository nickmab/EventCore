// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoApp.h"

#include "Core/Events/Utility/EventPrinter.h"
#include "Core/Logger.h"

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
	mOnTickProducer.reset(new OnTickProducer(
		std::bind(&EventQueue::EnqueueEvent, &GetEventQueue(), std::placeholders::_1),
		1000));
	
	RegisterEventProducer(mOnTickProducer.get());

	mEventPrinter.reset(new EventPrinter());
	GetEventQueue().RegisterConsumer(mEventPrinter.get());
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