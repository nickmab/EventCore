#pragma once

#include "Core/Application.h"
#include "Core/Events/TickEvent.h"

namespace EventCore {

	class TickEventProducer : public EventProducer
	{
	public:
		TickEventProducer(int millisFrequency, EventCallbackFn callback = nullptr);
		
	private:
		double mSecondsFrequency;
		std::chrono::time_point<std::chrono::system_clock> mLastRunTime;

		virtual void EventProducerOnUpdate() override;
	};

}