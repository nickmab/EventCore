#pragma once

#include <Core/Application.h>

#include <iostream>

class DemoApp : public EventCore::Application
{
public:
	DemoApp() = default;

private:
	int mSomeInteger{0};
	virtual void OnUpdate() override;
};

EventCore::Application* EventCore::CreateApplication();