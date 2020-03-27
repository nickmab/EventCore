#pragma once

#include <Core/Application.h>
#include <Core/Events/Utility/TickEventProducer.h>
#include <TCP/TCPClient.h>
#include <Core/Events/Utility/EventPrinter.h>
#include <Proto/ProtoParser.h>

#include "QandARouter.h"
#include "QuestionGenerator.h"

using namespace EventCore;

class MathClient : public Application
{
public:
	void SendQuestion(const ProtoMsgVariant&);

private:
	std::unique_ptr<TCPClient> mTCPClient{nullptr};
	std::unique_ptr<TickEventProducer> mTickEventProducer{nullptr};
	std::unique_ptr<QAndARouter> mRouter{nullptr};
	std::unique_ptr<QuestionGenerator> mQuestionGen{nullptr};

	virtual void Init() override;
	virtual void OnUpdate() override;
};

Application* CreateApplication();