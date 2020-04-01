#pragma once

#include "TCPSession.h"
#include "Proto/ProtoParser.h"

namespace EventCore {

    // This is the thing that actually _owns_ the parser (and the events it produces/consumes).
    struct TCPDataInterface
    {
        TCPDataInterface(ProtoParser*, SOCKET, size_t initialRecvBufSize = 1024);
        ~TCPDataInterface();
        TCPSession mSession;
        std::unique_ptr<ProtoParser> mParser;
    };

}