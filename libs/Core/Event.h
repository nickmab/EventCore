#pragma once

#include <string>

namespace EventCore {

	class Event
	{
	public:

		enum Type
		{
			OnTick = 1,
		};

		inline virtual Event::Type GetType() const = 0;
		inline virtual const char* const GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

}