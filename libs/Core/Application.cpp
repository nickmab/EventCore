#include "pch.h"

#include "Application.h"

int main(int argc, char* argv[])
{
    return EventCore::EntryPoint::MainFunction(argc, argv);
}

namespace EventCore {

    Application* Application::sInstance = nullptr;

    void Application::Shutdown(int exitCode)
    {
        mExitCode = exitCode; 
        mIsRunning = false;
    }

    void Application::RegisterEventProducer(EventProducer* producer)
    {
        mEventProducers.push_back(producer);
    }

    void Application::UnregisterEventProducer(EventProducer* producer)
    {
        // should check that this actually works...
        auto it = std::find(mEventProducers.begin(), mEventProducers.end(), producer);
        if (it != mEventProducers.end())
            mEventProducers.erase(it);
    }

    void Application::RegisterEventConsumer(EventConsumer* consumer)
    {
        mEventQueue.RegisterConsumer(consumer);
    }

    void Application::UnregisterEventConsumer(EventConsumer* consumer)
    {
        mEventQueue.UnregisterConsumer(consumer);
    }

    void Application::Run()
    {
        for (;;)
        {
            if (mIsRunning)
                OnUpdate();
            else
                return;

            for (auto* producer : mEventProducers)
                if (mIsRunning)
                    producer->EventProducerOnUpdate();
                else
                    return;

            if (mIsRunning)
                mEventQueue.PublishEvents();
            else
                return;
        }
    }

    void Application::OnConsoleSignal(ConsoleSignal sig)
    {
        LOGF_CRITICAL("Signal: {}", sig);
        Shutdown(0);
    }

    int EntryPoint::MainFunction(int argc, char* argv[])
    {
        if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
        {
            LOG_CRITICAL("Unable to install console signal handler!");
            return -1;
        }        
        
        std::filesystem::path thisBinaryPath = argv[0];
        const std::string thisBinaryName = thisBinaryPath.filename().replace_extension("").string();
    
        Application* instance = CreateApplication(argc, argv);
        if (!instance)
        {
            LOG_CRITICAL("Unable to create application! Shutting down.");
            return -1;
        }

        Application::sInstance = instance;
        instance->mBinaryName = thisBinaryName;

        LOG_WARN("Initializing application...");
        instance->Init();
        
        LOG_WARN("Entering run loop of application...");
        instance->Run();
        
        int exitCode = instance->mExitCode;
        LOG_WARN("Destroying application instance...");
        delete instance;
        
        LOGF_WARN("Exiting with code: {}", exitCode);
        return exitCode;
    }

    BOOL WINAPI EntryPoint::ConsoleHandler(DWORD CEvent)
    {
        Application& app = Application::Get();

        switch (CEvent)
        {
        case CTRL_C_EVENT:
            app.OnConsoleSignal(Application::ConsoleSignal::CTRL_C);
            break;
        case CTRL_BREAK_EVENT:
            app.OnConsoleSignal(Application::ConsoleSignal::BREAK);
            break;
        case CTRL_CLOSE_EVENT:
            app.OnConsoleSignal(Application::ConsoleSignal::CLOSE);
            break;
        case CTRL_LOGOFF_EVENT:
            app.OnConsoleSignal(Application::ConsoleSignal::LOGOFF);
            break;
        case CTRL_SHUTDOWN_EVENT:
            app.OnConsoleSignal(Application::ConsoleSignal::SHUTDOWN);
            break;
        }
        return TRUE;
    }
        
}