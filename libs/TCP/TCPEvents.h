#pragma once

#include "Core/Event.h"

#include "TCPSession.h"

namespace EventCore {

// throwaway macro
#define TCP_EVT(who, what) \
	class TCP ## who ## what ## Event : public Event \
	{ \
	public: \
		TCP ## who ## what ## Event( \
			const EventProducer* sender, \
			TCPSession::SessionId, \
			std::string name = "(unnamed)"); \
\
		inline virtual Event::Type GetType() const override { return Event::Type::TCP ## who ## what ## ; } \
		inline virtual const char* const GetName() const override { return "TCP" #who #what "Event"; } \
\
		virtual std::string ToString() const override; \
\
		inline TCPSession::SessionId GetSessionId() const { return mSessionId; } \
\
	private: \
		TCPSession::SessionId mSessionId; \
		std::string mName; \
	};

	TCP_EVT(Client, Connected)
	TCP_EVT(Client, Disconnected)
	TCP_EVT(Server, Connected)
	TCP_EVT(Server, Disconnected)

#undef TCP_EVT

}
