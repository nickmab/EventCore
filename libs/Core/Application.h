#pragma once

#ifndef _WIN32
    #error "Project currently only supports Windows, sorry."
#endif

#include "Event.h"

int main(int argc, char* argv[]);

namespace EventCore {

    // Application singleton.
    // Takes ownership of Events when they are raised 
    // (via the EventQueue instance). 
    // They are freed after the OnEvent callback loop.
    class Application
    {
        friend class EntryPoint;

    public:
        virtual ~Application() {}
        void Shutdown(int exitCode = 0);
        
        static Application& Get() { return *sInstance; }
        inline const std::string GetBinaryName() const { return mBinaryName; }
        inline bool IsRunning() const { return mIsRunning; }

        // Whatever creates the EventProducer is responsible for 
        // the memory/lifetime AND including ensuring that it is
        // unregistered from here before/when the memory is freed.
        void RegisterEventProducer(EventProducer*);
        void UnregisterEventProducer(EventProducer*);

        // As above for the producers.
        void RegisterEventConsumer(EventConsumer*);
        void UnregisterEventConsumer(EventConsumer*);
        
        EventQueue& GetEventQueue() { return mEventQueue; }

    private:
        static Application* sInstance;
        std::string mBinaryName;
        
        virtual void Init() = 0;
        virtual void OnUpdate() = 0;
        
        void Run();

        enum class ConsoleSignal
        {
            CTRL_C = 0,
            BREAK,
            CLOSE,
            LOGOFF,
            SHUTDOWN
        };
        // Could eventually make this virtual and incorporate
        // a whole interface for this, but yeah nah.
        void OnConsoleSignal(ConsoleSignal);

        bool mIsRunning{true};
        int mExitCode{0};

        // The EventQueue takes ownership of the Events when they are raised.
        EventQueue mEventQueue;
        // The Application base class does NOT own these event producers.
        std::vector<EventProducer*> mEventProducers;
    };

    // Application must be subclassed by an app that uses this class, 
    // and it must implement this function to return the application instance.
    Application* CreateApplication();

    class EntryPoint
    {
    public:
        static int MainFunction(int argc, char* argv[]);

        static BOOL WINAPI ConsoleHandler(DWORD dwCtrlType);
    };
    
}