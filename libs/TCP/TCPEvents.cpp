#include "pch.h"

#include "TCPEvents.h"

namespace EventCore {

    TCPConnectionEvent::TCPConnectionEvent(
        const EventProducer* sender, 
        TCPSession::SessionId sessionId, 
        TCPConnectionEvent::Type type)
        : Event(sender) 
        , mSessionId(sessionId) 
        , mType(type) 
    {} 

    std::string TCPConnectionEvent::ToString() const
    { 
        std::stringstream ss; 
        ss << "TCPConnectionEvent type " << (int)mType <<", sessionId " << mSessionId << "."; 
        return ss.str(); 
    }

}