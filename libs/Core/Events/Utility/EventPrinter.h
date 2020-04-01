#pragma once

#include "Core/Events/EventQueue.h"

namespace EventCore {

    class EventPrinter : public EventConsumer
    {
    public:
        virtual bool DoesCareAboutEventType(Event::Type) const override;
        virtual void OnEvent(const Event&) override;
    };

}