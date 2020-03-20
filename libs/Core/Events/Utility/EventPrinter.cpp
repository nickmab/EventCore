#include "EventPrinter.h"
#include "Core/Logger.h"

namespace EventCore {

	bool EventPrinter::DoesCareAboutEventType(Event::Type type) const
	{
		return type == Event::Type::OnTick;
	}
	
	void EventPrinter::OnEvent(const Event& evt)
	{
		LOGF_INFO("EventPrinter says: {}", evt.ToString());
	}

}