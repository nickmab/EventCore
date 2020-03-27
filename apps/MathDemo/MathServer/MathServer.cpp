#include <pch.h>

#include "MathServer.h"

#include <Proto/ProtoParser.h>

namespace EventCore {
	Application* CreateApplication()
	{
		return new ::MathServer();
	}
}

using namespace EventCore;

void MathServer::Init()
{
	mServer.reset(new TCPServer(ProtoParser::Protocol::MathProto));
	RegisterEventProducer(mServer.get());

	mAnswerer.reset(new QuestionAnswerer());
	RegisterEventConsumer(mAnswerer.get());

	if (!mServer->Init())
	{
		LOG_CRITICAL("Could not initialize client; shutting down.");
		Shutdown(1);
	}
}

void MathServer::OnUpdate()
{
	if (!mServer->OnUpdate())
	{
		LOG_CRITICAL("Encountered some kind of error; shutting down.");
		Shutdown(1);
	}
}

void MathServer::SendAnswer(TCPSession::SessionId sessionId, const ProtoMsgVariant& msg)
{
	if (!mServer->QueueOutgoingMessage(sessionId, msg))
	{
		LOGF_CRITICAL("Unable to queue outgoing message to session ID {}: {}",
			sessionId,
			std::visit([](const auto& arg) -> std::string { return arg.DebugString(); },
				msg));
		Shutdown(1);
	}
}