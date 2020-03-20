#include "TCPEvents.h"

#include <sstream>

namespace EventCore {

	TCPClientConnected::TCPClientConnected(std::string clientName)
		: mClientName(clientName)
	{}

	std::string TCPClientConnected::ToString() const
	{
		std::stringstream ss;
		ss << "TCPClientConnectedEvent: " << mClientName;
		return ss.str();
	}

	TCPClientDisconnected::TCPClientDisconnected(std::string clientName)
		: mClientName(clientName)
	{}

	std::string TCPClientDisconnected::ToString() const
	{
		std::stringstream ss;
		ss << "TCPClientDisconnectedEvent: " << mClientName;
		return ss.str();
	}
}