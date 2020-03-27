#pragma once

#include <Core/Event.h>
#include <Proto/MathProto/MathProto.pb.h>

using namespace EventCore;

// forward dec
class QAndARouter;

class QuestionAsker
{
public:
	QuestionAsker(QAndARouter&);
	virtual ~QuestionAsker() {}

	virtual void HandleResponse(const mathproto::ArithmeticResponse&) = 0;

protected:
	QAndARouter& mRouter;
};

class QAndARouter : public EventConsumer
{
public:
	void SendQuestion(QuestionAsker*, const mathproto::ArithmeticRequest&);
	
	virtual bool DoesCareAboutEventType(Event::Type) const override;

private:
	std::map<uint64_t, QuestionAsker*> mQuestionToAskerMap;

	// This is basically the "answer handler" function.
	virtual void On_mathproto_ArithmeticResponse(
		const ProtoMessageReceivedEvent&,
		const mathproto::ArithmeticResponse&) override;
};