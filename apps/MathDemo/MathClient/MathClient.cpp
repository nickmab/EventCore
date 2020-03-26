#include "MathClient.h"

#include <Core/Logger.h>
#include <Proto/ProtoParser.h>

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::MathClient();
	}
}

using namespace EventCore;

void MathClient::Init()
{
	mEventPrinter.reset(new EventPrinter());
	RegisterEventConsumer(mEventPrinter.get());

	mTCPClient.reset(new TCPClient(ProtoParser::Protocol::MathProto));
	RegisterEventProducer(mTCPClient.get());

	if (!mTCPClient->Init())
	{
		LOG_CRITICAL("Could not initialize client; shutting down.");
		Shutdown(1);
	}
}

void MathClient::OnUpdate()
{
	if (!mTCPClient->OnUpdate())
	{
		LOG_CRITICAL("Encountered some kind of error; shutting down.");
		Shutdown(1);
	}
}