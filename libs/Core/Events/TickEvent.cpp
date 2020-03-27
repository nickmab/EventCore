#include "pch.h"

#include "TickEvent.h"

namespace EventCore {

    TickEvent::TickEvent(const EventProducer* sender)
        : Event(sender)
    {}

}