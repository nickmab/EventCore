#pragma once

#include <Core/Application.h>
#include <TCP/TCPClient.h>

class DemoClient : public EventCore::Application
{
	EventCore::TCPClient mTCPClient;

	virtual void Init() override;
	virtual void OnUpdate() override;
};

EventCore::Application* EventCore::CreateApplication();