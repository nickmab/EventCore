#include "TCPUtils.h"

#include <WS2tcpip.h>

#include <iostream>

namespace EventCore {

	void TCPError(const std::string& msg, std::optional<int> systemErrorCode)
	{
		if (!msg.empty())
			std::cout << msg << std::endl;

		if (!systemErrorCode)
		{
			systemErrorCode.emplace(WSAGetLastError());
		}

		// See: http://msdn.microsoft.com/en-us/library/ms679351(VS.85).aspx
		LPSTR errString = nullptr;

		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			0, systemErrorCode.value(), 0, (LPSTR)&errString, 0, 0);

		std::stringstream ss;
		ss << "TCPServer error (code " << systemErrorCode.value() << "): " << errString;
		std::cout << ss.str() << std::endl;

		LocalFree(errString);
	}

}