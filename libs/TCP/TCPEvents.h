#pragma once

#include "Core/Event.h"

namespace EventCore {

// throwaway macro
#define TCP_EVT(who, what) \
	class TCP##who##what : public Event \
	{ \
	public: \
		TCP##who##what(std::string name = "(unnamed)"); \
\
		inline virtual Event::Type GetType() const override { return Event::Type::TCP##who##what; } \
		inline virtual const char* const GetName() const override { return "TCP##who##whatEvent"; } \
\
		virtual std::string ToString() const override; \
\
	private: \
		std::string mName; \
	};

	TCP_EVT(Client, Connected)
	TCP_EVT(Client, Disconnected)
	TCP_EVT(Server, Connected)
	TCP_EVT(Server, Disconnected)

#undef TCP_EVT

}
