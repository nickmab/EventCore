#include "EventPrinter.h"
#include "Core/Logger.h"

namespace EventCore {

	bool EventPrinter::DoesCareAboutEventType(Event::Type type) const
	{
		// we just print any event.
		return true;
	}
	
	void EventPrinter::OnEvent(const Event& evt)
	{
		LOGF_INFO("EventPrinter says: {}", evt.ToString());
	}

}