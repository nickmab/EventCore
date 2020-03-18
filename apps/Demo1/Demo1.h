// EventCore.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

// TODO: Reference additional headers your program requires here.

#include <Core/Application.h>

class DemoApp : public EventCore::Application
{
public:
	DemoApp() = default;

private:
	int mSomeInteger{0};
	virtual void OnUpdate() override;
};

EventCore::Application* EventCore::CreateApplication();