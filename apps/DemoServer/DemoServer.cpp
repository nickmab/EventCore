﻿// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoServer.h"

#include "Core/Events/Utility/EventPrinter.h"
#include "Core/Logger.h"

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::DemoServer();
	}
}

ProtoParser* DemoServer::NewProtoParser()
{
	// This function lives here so we can bind it to the correct event production callback. 
	// I don't fully love this pattern, it might change.
	return new DemoProtoParser(
		std::bind(&EventQueue::EnqueueEvent, &GetEventQueue(), std::placeholders::_1));
}

void DemoServer::Init()
{
	mOnTickProducer.reset(new OnTickProducer(
		std::bind(&EventQueue::EnqueueEvent, &GetEventQueue(), std::placeholders::_1),
		1000));
	
	RegisterEventProducer(mOnTickProducer.get());

	EventPrinter* consumer = new EventPrinter();
	GetEventQueue().RegisterConsumer(std::shared_ptr<EventConsumer>(consumer));

	mServer.reset(new TCPServer(std::bind(&DemoServer::NewProtoParser, this)));

	if (!mServer->Init())
	{
		LOG_CRITICAL("Could not initialize server; shutting down.");
		Shutdown(1);
	}
}

void DemoServer::OnUpdate()
{
	if (!mServer->OnUpdate())
	{
		LOG_CRITICAL("Encountered some kind of error in server; shutting down.");
		Shutdown(1);
	}
}