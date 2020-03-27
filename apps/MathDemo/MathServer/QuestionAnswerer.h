#pragma once

#include "MathServer.h"

using namespace EventCore;

class QuestionAnswerer : public EventConsumer
{
public:
    QuestionAnswerer();

    virtual bool DoesCareAboutEventType(Event::Type) const override;
    
private:
    virtual void On_mathproto_ArithmeticRequest(
        const ProtoMessageReceivedEvent&,
        const mathproto::ArithmeticRequest&) override;
};