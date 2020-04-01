#pragma once

#include "TCPSession.h"
#include "TCPDataInterface.h"

namespace EventCore {

    static const ULONG DEFAULT_IN_ADDR = INADDR_ANY;
    static const USHORT DEFAULT_LISTENING_PORT = 54000;

    // This needs to be both a producer and consumer of events.
    // Might eventually turn it into an abstract class and make something else impl a protocol...
    class TCPServer : public EventProducer
    {
    public:
        TCPServer(
            ProtoParser::Protocol,
            EventProducer::EventCallbackFn evtCallback = nullptr,
            ULONG inAddr = DEFAULT_IN_ADDR, 
            USHORT listeningPort = DEFAULT_LISTENING_PORT);
        ~TCPServer();
        
        // For the below public methods, if an error is encountered it will return false
        // and also call "void EventCore::TCPError()" to fetch and log the error/reason.
        
        // Create the listening socket, bind and listen.
        // If success, mRunning will be set to true and subsequent calls to OnUpdate 
        // will allow us to accept incoming client connections etc.
        bool Init();
        bool OnUpdate();
        
        void Shutdown();

        bool QueueOutgoingMessage(TCPSession::SessionId, const ProtoMsgVariant&);

    private:
        sockaddr_in mSockAddrIn;
        SOCKET mListeningSocket{0};
        fd_set mFDSet{0};

        ProtoParser::Protocol mProtocol;

        // TCPDataInterface actually _owns_ the parser (and the events it produces/consumes).
        // The use of unique_ptr here is due to the awkwardness of construction and moving/emplacement
        // within the map (awkard due to the way I chose to key this map on session ID. No biggie. Fix later.
        std::map<TCPSession::SessionId, std::unique_ptr<TCPDataInterface> > mClientMap;
        // I freely admit this is a horrendous hack but it will do for now. 
        // The above is keyed on session id for the sake of writing/queueing/routing
        // outgoing messages, but when we choose a socket to _read_ from using the select function,
        // we do need to look up the right client by its socket, not the TCPSessionId.
        // Returns nullptr if not found.
        TCPDataInterface* FindClientInClientMapBySocket(SOCKET);

        bool mInitialized{false};
        bool mRunning{false};
        bool mShutdown{false};

        
    };

}