#pragma once

#include "MathServer.h"

using namespace EventCore;
using namespace mathproto;

class QuestionAnswerer : public EventConsumer
{
public:
    QuestionAnswerer();

    virtual bool DoesCareAboutEventType(Event::Type) const override;
    
private:
    virtual void On_mathproto_ArithmeticRequest(
        const ProtoMessageReceivedEvent&,
        const ArithmeticRequest&) override;
};