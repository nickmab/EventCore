#include <pch.h>

#include "QandARouter.h"

#include "MathClient.h"

#include <Core/Application.h>

QuestionAsker::QuestionAsker(QAndARouter& router)
	: mRouter(router)
{}

void QAndARouter::SendQuestion(QuestionAsker* asker, const mathproto::ArithmeticRequest& question)
{
	mQuestionToAskerMap[question.request_id()] = asker;
	static_cast<MathClient*>(&Application::Get())->SendQuestion(question);
}

bool QAndARouter::DoesCareAboutEventType(Event::Type type) const
{
	return type == Event::Type::ProtoMessageReceived;
}

void QAndARouter::On_mathproto_ArithmeticResponse(
	const ProtoMessageReceivedEvent&,
	const mathproto::ArithmeticResponse& msg)
{
	auto asker = mQuestionToAskerMap.find(msg.request_id());
	if (asker == mQuestionToAskerMap.end())
	{
		LOGF_CRITICAL("Got an answer to an unrecognised question: {}", msg.DebugString());
		Application::Get().Shutdown(1);
		return;
	}

	asker->second->HandleResponse(msg);
	mQuestionToAskerMap.erase(msg.request_id());
}