#include "DemoServer.h"

#include "Core/Logger.h"
#include <Proto/ProtoParser.h>

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::DemoServer();
	}
}

void DemoServer::Init()
{
	mTickEventProducer.reset(new TickEventProducer(1000));
	RegisterEventProducer(mTickEventProducer.get());

	mEventPrinter.reset(new EventPrinter());
	RegisterEventConsumer(mEventPrinter.get());

	mServer.reset(new TCPServer(ProtoParser::Protocol::DemoProto));
	RegisterEventProducer(mServer.get());

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