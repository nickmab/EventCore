#pragma once

namespace EventCore {

    // another forward dec for later in this file.
    class EventProducer;

    class Event
    {
    public:
        Event(const EventProducer* sender);

        // ALL events MUST be added to this enum.
        enum class Type
        {
            Begin = 0,
            
            // Insert events in here. "Begin" and "End" are used just for iteration.
            Tick,
            TCPConnection,
            ProtoMessageReceived,
            
            // Insert events in the section above. "Begin" and "End" are used just for iteration.
            End
        };

        inline virtual Event::Type GetType() const = 0;
        inline virtual const char* const GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline const EventProducer* GetSender() const { return mSender; }

    private:
        const EventProducer* mSender;
    };

}