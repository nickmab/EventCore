#pragma once

#include "Core/Event.h"

namespace EventCore {

	class OnTickEvent : public Event
	{
	public:
		inline virtual Event::Type GetType() const override { return Event::Type::OnTick; }
		inline virtual const char* const GetName() const override { return "OnTickEvent"; }
	};

}