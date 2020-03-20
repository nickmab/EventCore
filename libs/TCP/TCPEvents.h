#pragma once

#include "Core/Event.h"

namespace EventCore {

	class TCPClientConnected : public Event
	{
	public:
		TCPClientConnected(std::string clientName);
		
		inline virtual Event::Type GetType() const override { return Event::Type::TCPClientConnected; }
		inline virtual const char* const GetName() const override { return "TCPClientConnectedEvent"; }

		virtual std::string ToString() const override;
		
	private:
		std::string mClientName;
	};

	class TCPClientDisconnected : public Event
	{
	public:
		TCPClientDisconnected(std::string clientName);

		inline virtual Event::Type GetType() const override { return Event::Type::TCPClientDisconnected; }
		inline virtual const char* const GetName() const override { return "TCPClientDisconnectedEvent"; }

		virtual std::string ToString() const override;

	private:
		std::string mClientName;
	};

}