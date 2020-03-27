#pragma once

#include <Core/Event.h>
#include <Proto/MathProto/MathProto.pb.h>

#include "QandARouter.h"

class ArithmeticRequestFactory
{
public:
    static ArithmeticRequest* New();
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

    virtual void HandleResponse(const ArithmeticResponse&) override;

private:
    void PoseAQuestion();

    int RandomOperator() const;
    double RandomOperand() const;

    std::map<uint64_t, std::unique_ptr<ArithmeticRequest> > mOutstandingQuestions;
};