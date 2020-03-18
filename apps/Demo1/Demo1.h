#pragma once

#include <Core/Application.h>

#include <chrono>

class DemoApp : public EventCore::Application
{
public:
	DemoApp(double secondsToStayAlive);

private:
	double mSecondsToStayAlive;
	std::chrono::time_point<std::chrono::system_clock> mApplicationStartTime;
	
	virtual void Init() override;
	virtual void OnUpdate() override;
};

EventCore::Application* EventCore::CreateApplication();