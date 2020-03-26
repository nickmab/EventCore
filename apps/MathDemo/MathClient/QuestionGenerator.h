#pragma once

#include <Core/Event.h>
#include <Proto/MathProto/MathProto.pb.h>

#include "QandARouter.h"

#include <map>
#include <memory>

using namespace EventCore;

class ArithmeticRequestFactory
{
public:
	static mathproto::ArithmeticRequest* New();
private:
	static uint64_t sUniqueId;
};

class QuestionGenerator
	: public EventConsumer
	, public QuestionAsker
{
public:
	QuestionGenerator(QAndARouter&);

	virtual bool DoesCareAboutEventType(Event::Type) const override;
	virtual void OnTick(const TickEvent&) override;

	virtual void HandleResponse(const mathproto::ArithmeticResponse&) override;

private:
	void PoseAQuestion();

	std::map<uint64_t, std::unique_ptr<mathproto::ArithmeticRequest> > mOutstandingQuestions;
};