#pragma once

#include <Core/Application.h>
#include <Core/Events/Utility/TickEventProducer.h>
#include <Core/Events/Utility/EventPrinter.h>
#include <TCP/TCPServer.h>

#include <memory>

using namespace EventCore;

class MathServer : public Application
{
	std::unique_ptr<TCPServer> mServer{ nullptr };
	std::unique_ptr<TickEventProducer> mTickEventProducer{ nullptr };
	std::unique_ptr<EventPrinter> mEventPrinter{ nullptr };

	virtual void Init() override;
	virtual void OnUpdate() override;
};

Application* CreateApplication();