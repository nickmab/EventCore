#include "EventPrinter.h"

#include <iostream>

namespace EventCore {

	bool EventPrinter::DoesCareAboutEventType(Event::Type type) const
	{
		return type == Event::Type::OnTick;
	}
	
	void EventPrinter::OnEvent(const Event& evt)
	{
		std::cout << "EventPrinter says... " << evt.ToString() << std::endl;
	}

}