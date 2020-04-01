#pragma once

#include "Core/Events/Event.h"

#include "TCPSession.h"

namespace EventCore {

    class EventProducer;

    class TCPConnectionEvent : public Event
    {
    public:

        enum class Type
        {
            ClientConnected = 0,
            ClientDisconnected,
            ServerConnected,
            ServerDisconnected
        };
        
        TCPConnectionEvent(
            const EventProducer* sender,
            TCPSession::SessionId,
            TCPConnectionEvent::Type);

        inline virtual Event::Type GetType() const override { return Event::Type::TCPConnection; }
        inline virtual const char* const GetName() const override { return "TCPConnectionEvent"; }

        virtual std::string ToString() const override; 

        inline TCPSession::SessionId GetSessionId() const { return mSessionId; } 

    private: 
        TCPSession::SessionId mSessionId; 
        TCPConnectionEvent::Type mType;
    };

}
