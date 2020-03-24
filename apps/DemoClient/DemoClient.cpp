// EventCore.cpp : Defines the entry point for the application.
//

#include "DemoClient.h"
#include "Core/Logger.h"

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::DemoClient(DemoProtoParser::New());
	}
}

using namespace EventCore;

DemoClient::DemoClient(ProtoParser* parser)
	: mTCPClient(parser)
{
}

void DemoClient::Init()
{
	if (!mTCPClient.Init())
	{
		LOG_CRITICAL("Could not initialize client; shutting down.");
		Shutdown(1);
	}
}

void DemoClient::OnUpdate()
{
	// temporary crappy hack
	if (!mHasSentMessageYet)
	{
		demoproto::NumericMessage msg;
		msg.set_an_integer(6123);
		msg.set_a_double(42.1);
		bool success = mTCPClient.QueueWriteData(msg);
		if (!success)
		{
			LOGF_CRITICAL("Encountered an error queuing msg to send: {}", msg.DebugString());
			Shutdown(1);
		}

		demoproto::TextualMessage msg2;
		msg2.set_a_sentence("I got the message!");
		msg2.set_is_interesting(false);
		success = mTCPClient.QueueWriteData(msg2);

		if (!success)
		{
			LOGF_CRITICAL("Encountered an error queuing msg to send: {}", msg2.DebugString());
			Shutdown(1);
		}

		mHasSentMessageYet = true;
	}
	
	// temporary crappy hack...
	if (!mTCPClient.OnUpdate())
	{
		LOG_CRITICAL("Encountered some kind of error; shutting down.");
		Shutdown(1);
	}
}