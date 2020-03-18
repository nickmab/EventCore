#pragma once

#include "Core/Event.h"

namespace EventCore {

	class EventPrinter : public EventConsumer
	{
	public:
		virtual bool DoesCareAboutEventType(Event::Type) const override;
		virtual void OnEvent(const Event&) override;
	};

}