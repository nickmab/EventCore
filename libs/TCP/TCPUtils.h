#pragma once

namespace EventCore {

    // Logs the custom string message if provided.
    // If an error code is *not* provided, will call WSAGetLastError under the hood.
    // Attempts to retrieve the string representation of the system error code
    // using FormatMessage under the hood.
    void TCPError(const std::string& msg = "", std::optional<int> systemErrorCode = std::nullopt);

}