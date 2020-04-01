#pragma once

#include "Core/Events/EventQueue.h"

namespace EventCore {

    class TickEventProducer : public EventProducer
    {
    public:
        TickEventProducer(int millisFrequency);
        
    private:
        double mSecondsFrequency;
        std::chrono::time_point<std::chrono::system_clock> mLastRunTime;

        virtual void EventProducerOnUpdate() override;
    };

}