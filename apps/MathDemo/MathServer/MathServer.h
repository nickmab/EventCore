#pragma once

#include <Core/Application.h>
#include <Core/Event.h>
#include <TCP/TCPServer.h>

#include "QuestionAnswerer.h"

#include <memory>

using namespace EventCore;

// forward dec for circularity.
class QuestionAnswerer;

class MathServer : public Application
{
public:
	void SendAnswer(TCPSession::SessionId, const ProtoMsgVariant&);

private:
	std::unique_ptr<TCPServer> mServer{nullptr};
	std::unique_ptr<QuestionAnswerer> mAnswerer{nullptr};

	virtual void Init() override;
	virtual void OnUpdate() override;
};

Application* CreateApplication();