#include "TCPEvents.h"

#include <sstream>

namespace EventCore {

// throwaway macro
#define TCP_EVT_IMPL(who, what) \
	TCP##who##what::TCP##who##what(std::string name) \
		: mName(name) \
	{} \
\
	std::string TCP##who##what::ToString() const \
	{ \
		std::stringstream ss; \
		ss << "TCP##who##whatEvent: " << mName; \
		return ss.str(); \
	}

	TCP_EVT_IMPL(Client, Connected)
	TCP_EVT_IMPL(Client, Disconnected)
	TCP_EVT_IMPL(Server, Connected)
	TCP_EVT_IMPL(Server, Disconnected)

#undef TCP_EVT_IMPL
}