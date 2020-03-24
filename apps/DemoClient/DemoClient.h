#pragma once

#include <Core/Application.h>
#include <TCP/TCPClient.h>
#include <Proto/DemoProto/DemoProtoParser.h>

class DemoClient : public EventCore::Application
{
public:
	DemoClient(EventCore::ProtoParser*);

private:
	EventCore::TCPClient mTCPClient;

	virtual void Init() override;
	virtual void OnUpdate() override;
};

EventCore::Application* EventCore::CreateApplication();