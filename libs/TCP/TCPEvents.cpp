#include "TCPEvents.h"

#include <sstream>

namespace EventCore {

// throwaway macro
#define TCP_EVT_IMPL(who, what) \
	TCP ## who ## what ## Event::TCP ## who ## what ## Event( \
		const EventProducer* sender, \
		TCPSession::SessionId sessionId, \
		std::string name) \
		: Event(sender) \
		, mSessionId(sessionId) \
		, mName(name) \
	{} \
\
	std::string TCP ## who ## what ## Event::ToString() const \
	{ \
		std::stringstream ss; \
		ss << "TCP" #who #what "Event: sessionId " << mSessionId << ", name " << mName; \
		return ss.str(); \
	}

	TCP_EVT_IMPL(Client, Connected)
	TCP_EVT_IMPL(Client, Disconnected)
	TCP_EVT_IMPL(Server, Connected)
	TCP_EVT_IMPL(Server, Disconnected)

#undef TCP_EVT_IMPL
}