#pragma once

#include <Core/Application.h>
#include <TCP/TCPServer.h>

#include <chrono>

class DemoServer : public EventCore::Application
{
public:
	DemoServer(double secondsToStayAlive);

private:
	double mSecondsToStayAlive;
	std::chrono::time_point<std::chrono::system_clock> mApplicationStartTime;

	EventCore::TCPServer mServer;
	
	virtual void Init() override;
	virtual void OnUpdate() override;
};

EventCore::Application* EventCore::CreateApplication();