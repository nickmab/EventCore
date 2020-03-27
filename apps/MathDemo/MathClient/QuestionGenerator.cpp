#include <pch.h>

#include "QuestionGenerator.h"

#include <Core/Application.h>

uint64_t ArithmeticRequestFactory::sUniqueId = 0;

ArithmeticRequest* ArithmeticRequestFactory::New()
{
    auto* instance = new ArithmeticRequest();
    instance->set_request_id(sUniqueId++);
    return instance;
}

QuestionGenerator::QuestionGenerator(QAndARouter& router)
    : EventConsumer()
    , QuestionAsker(router)
{
    srand((unsigned)time(0));
}

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
    ArithmeticRequest* request = ArithmeticRequestFactory::New();
    request->set_lhs(RandomOperand());
    request->set_op(static_cast<ArithmeticOperator>(RandomOperator()));
    request->set_rhs(RandomOperand());
    mOutstandingQuestions.emplace(request->request_id(), request);
    mRouter.SendQuestion(this, *request);
}

int QuestionGenerator::RandomOperator() const
{
    return rand() % 4;
}

double QuestionGenerator::RandomOperand() const
{
    // crappy hard coded to numbers between -100 and 100
    return 200.0 * (-0.5 + (float)rand() / RAND_MAX);
}

void QuestionGenerator::HandleResponse(const ArithmeticResponse& response)
{
    auto request = mOutstandingQuestions.find(response.request_id());
    if (request == mOutstandingQuestions.end())
    {
        LOGF_CRITICAL("Received response to question I didn't ask! {}", response.DebugString());
        Application::Get().Shutdown(1);
        return;
    }
    
    auto& qn = *request->second;
    auto des = ArithmeticOperator_descriptor();
    auto opName = des->FindValueByNumber(qn.op())->name();
    LOGF_WARN("The question was: {:.2f} {} {:.2f} (request ID: {})", 
        qn.lhs(), opName, qn.rhs(), qn.request_id());
    LOGF_WARN("The answer is: {:.2f}", response.result());
    mOutstandingQuestions.erase(request);
}