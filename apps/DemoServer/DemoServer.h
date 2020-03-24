#pragma once

#include <Core/Application.h>
#include <TCP/TCPServer.h>
#include <Proto/DemoProto/DemoProtoParser.h>

class DemoServer : public EventCore::Application
{
public:
	DemoServer() {}

private:
	EventCore::TCPServer mServer{EventCore::DemoProtoParser::New};
	
	virtual void Init() override;
	virtual void OnUpdate() override;
};

EventCore::Application* EventCore::CreateApplication();