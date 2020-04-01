#pragma once

#include "Event.h"

namespace EventCore {

    class EventProducer;

    class TickEvent : public Event
    {
    public:
        TickEvent(const EventProducer* sender);

        inline virtual Event::Type GetType() const override { return Event::Type::Tick; }
        inline virtual const char* const GetName() const override { return "TickEvent"; }
    };

}