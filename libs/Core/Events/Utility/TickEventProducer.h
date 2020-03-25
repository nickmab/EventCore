#pragma once

#include "Core/Events/TickEvent.h"
#include <chrono>

namespace EventCore {

	class TickEventProducer : public EventProducer
	{
	public:
		TickEventProducer(EventCallbackFn, int millisFrequency);
		
	private:
		double mSecondsFrequency;
		std::chrono::time_point<std::chrono::system_clock> mLastRunTime;

		virtual void EventProducerOnUpdate() override;
	};

}