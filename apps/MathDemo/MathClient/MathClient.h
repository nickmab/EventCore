#pragma once

#include <Core/Application.h>
#include <TCP/TCPClient.h>
#include <Core/Events/Utility/EventPrinter.h>

#include <memory>

using namespace EventCore;

class MathClient : public Application
{
	std::unique_ptr<TCPClient> mTCPClient{ nullptr };
	std::unique_ptr<EventPrinter> mEventPrinter{ nullptr };

	virtual void Init() override;
	virtual void OnUpdate() override;
};

Application* CreateApplication();