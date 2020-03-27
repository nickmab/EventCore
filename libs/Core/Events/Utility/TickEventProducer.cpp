#include "pch.h"

#include "TickEventProducer.h"

namespace EventCore {

	TickEventProducer::TickEventProducer(int millisFrequency, EventCallbackFn callback)
		: EventProducer(callback)
		, mSecondsFrequency(1e-3 * (double)millisFrequency)
	{}

	void TickEventProducer::EventProducerOnUpdate()
	{
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = now - mLastRunTime;
		if (diff.count() > mSecondsFrequency)
		{
			mLastRunTime = now;
			RaiseEvent(new TickEvent(this));
		}
	}

}