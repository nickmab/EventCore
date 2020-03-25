#pragma once

#include "Core/Events/OnTick.h"
#include <chrono>

namespace EventCore {

	class OnTickProducer : public EventProducer
	{
	public:
		OnTickProducer(EventCallbackFn, int millisFrequency);
		
	private:
		double mSecondsFrequency;
		std::chrono::time_point<std::chrono::system_clock> mLastRunTime;

		virtual Event* OnUpdateImpl() override;
	};

}