#pragma once

#include <Core/Application.h>
#include <Core/Events/Utility/OnTickProducer.h>
#include <Core/Events/Utility/EventPrinter.h>

#include <chrono>
#include <memory>

using namespace EventCore;

class DemoApp : public Application
{
public:
	DemoApp(double secondsToStayAlive);

private:
	double mSecondsToStayAlive;
	std::chrono::time_point<std::chrono::system_clock> mApplicationStartTime;
	std::unique_ptr<OnTickProducer> mOnTickProducer{nullptr};
	std::unique_ptr<EventPrinter> mEventPrinter{nullptr};

	virtual void Init() override;
	virtual void OnUpdate() override;
};

Application* CreateApplication();