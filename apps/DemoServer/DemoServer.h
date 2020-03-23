#pragma once

#include <Core/Application.h>
#include <TCP/TCPServer.h>

class DemoServer : public EventCore::Application
{
public:
	DemoServer() {}

private:
	EventCore::TCPServer mServer;
	
	virtual void Init() override;
	virtual void OnUpdate() override;
};

EventCore::Application* EventCore::CreateApplication();