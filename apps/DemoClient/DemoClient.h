#pragma once

#include <memory>
#include <Core/Application.h>
#include <TCP/TCPClient.h>
#include <Proto/DemoProto/DemoProtoParser.h>

using namespace EventCore;

class DemoClient : public Application
{
	std::unique_ptr<TCPClient> mTCPClient{nullptr};
	std::unique_ptr<ProtoParser> mProtoParser{nullptr};
	bool mHasSentMessageYet{false};

	virtual void Init() override;
	virtual void OnUpdate() override;
};

Application* CreateApplication();