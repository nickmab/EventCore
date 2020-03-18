#pragma once

#include "Core/EventImpls/OnTick.h"
#include <chrono>

namespace EventCore {

	class OnTickProducer : public EventProducer
	{
	public:
		OnTickProducer(EventCallbackFn, int millisFrequency);
		
	private:
		double mSecondsFrequency;
		std::chrono::time_point<std::chrono::system_clock> mLastRunTime;

		virtual std::shared_ptr<Event> OnUpdateImpl() override;
	};

}