#include "pch.h"

#include "TCPUtils.h"

namespace EventCore {

    void TCPError(const std::string& msg, std::optional<int> systemErrorCode)
    {
        if (!msg.empty())
            LOG_ERROR(msg);

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
        LOG_ERROR(ss.str());

        LocalFree(errString);
    }

}