#include "pch.h"

#include "Event.h"

namespace EventCore {

    Event::Event(const EventProducer* sender)
        : mSender(sender)
    {} 

}