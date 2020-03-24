#pragma once

#include <Core/Application.h>
#include <Core/Events/Utility/OnTickProducer.h>
#include <TCP/TCPServer.h>
#include <Proto/DemoProto/DemoProtoParser.h>

#include <memory>

using namespace EventCore;

class DemoServer : public Application
{
public:
	DemoServer() {}

	ProtoParser* NewProtoParser();

private:
	std::unique_ptr<TCPServer> mServer{nullptr};
	std::unique_ptr<OnTickProducer> mOnTickProducer{ nullptr };

	virtual void Init() override;
	virtual void OnUpdate() override;
};

Application* CreateApplication();