#include "QuestionGenerator.h"

#include <Core/Application.h>
#include <Core/Logger.h>

uint64_t ArithmeticRequestFactory::sUniqueId = 0;

mathproto::ArithmeticRequest* ArithmeticRequestFactory::New()
{
	auto* instance = new mathproto::ArithmeticRequest();
	instance->set_request_id(sUniqueId++);
	return instance;
}

QuestionGenerator::QuestionGenerator(QAndARouter& router)
	: EventConsumer()
	, QuestionAsker(router)
{}

bool QuestionGenerator::DoesCareAboutEventType(Event::Type type) const
{
	return type == Event::Type::Tick;
}

void QuestionGenerator::OnTick(const TickEvent&)
{
	PoseAQuestion();
}

void QuestionGenerator::PoseAQuestion()
{
	mathproto::ArithmeticRequest* request = ArithmeticRequestFactory::New();
	request->set_lhs(3.5);
	request->set_op(mathproto::ArithmeticOperator::PLUS);
	request->set_rhs(7.1);
	mOutstandingQuestions.emplace(request->request_id(), request);
	mRouter.SendQuestion(this, *request);
}

void QuestionGenerator::HandleResponse(const mathproto::ArithmeticResponse& response)
{
	auto request = mOutstandingQuestions.find(response.request_id());
	if (request == mOutstandingQuestions.end())
	{
		LOGF_CRITICAL("Received response to question I didn't ask! {}", response.DebugString());
		Application::Get().Shutdown(1);
		return;
	}
	
	auto& qn = *request->second;
	auto des = mathproto::ArithmeticOperator_descriptor();
	auto opName = des->FindValueByNumber(qn.op())->name();
	LOGF_WARN("The question was: {} {} {} (request ID: {})", 
		qn.lhs(), opName, qn.rhs(), qn.request_id());
	LOGF_WARN("The answer is: {}", response.result());
	mOutstandingQuestions.erase(request);
}