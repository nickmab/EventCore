#pragma once

#include <Core/Application.h>
#include <TCP/TCPClient.h>
#include <Proto/DemoProto/DemoProtoParser.h>
#include <Core/Events/Utility/EventPrinter.h>

#include <memory>

using namespace EventCore;

class DemoClient : public Application
{
	std::unique_ptr<TCPClient> mTCPClient{nullptr};
	std::unique_ptr<ProtoParser> mProtoParser{nullptr};
	std::unique_ptr<EventPrinter> mEventPrinter{nullptr};
	bool mHasSentMessageYet{false};

	virtual void Init() override;
	virtual void OnUpdate() override;
};

Application* CreateApplication();