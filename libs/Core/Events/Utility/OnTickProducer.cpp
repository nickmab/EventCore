#include "OnTickProducer.h"

namespace EventCore {

	OnTickProducer::OnTickProducer(EventCallbackFn callback, int millisFrequency)
		: EventProducer(callback)
		, mSecondsFrequency(1e-3 * (double)millisFrequency)
	{}

	std::shared_ptr<Event> OnTickProducer::OnUpdateImpl()
	{
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = now - mLastRunTime;
		if (diff.count() > mSecondsFrequency)
		{
			mLastRunTime = now;
			return std::shared_ptr<Event>(new OnTickEvent());
		}
		return nullptr;
	}

}