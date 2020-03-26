#include "QuestionAnswerer.h"

QuestionAnswerer::QuestionAnswerer()
	: EventConsumer()
{}

bool QuestionAnswerer::DoesCareAboutEventType(Event::Type type) const
{
	return type == Event::Type::ProtoMessageReceived;
}

void QuestionAnswerer::On_mathproto_ArithmeticRequest(
	const ProtoMessageReceivedEvent& evt,
	const mathproto::ArithmeticRequest& request)
{
	mathproto::ArithmeticResponse answer;
	answer.set_request_id(request.request_id());

	switch (request.op())
	{
	case mathproto::ArithmeticOperator::PLUS:
		answer.set_result(request.lhs() + request.rhs());
		break;
	case mathproto::ArithmeticOperator::MINUS:
		answer.set_result(request.lhs() - request.rhs());
		break;
	case mathproto::ArithmeticOperator::TIMES:
		answer.set_result(request.lhs() * request.rhs());
		break;
	case mathproto::ArithmeticOperator::DIVBY:
		answer.set_result(request.lhs() / request.rhs());
		break;
	default:
		ASSERTF(false, "Unrecognised operator in message: {}", request.op());
		return;
	}

	static_cast<MathServer*>(&Application::Get())->SendAnswer(evt.GetSessionId(), answer);
}