#include "pch.h"

#include "Application.h"

#include "Event.h"

int main(int argc, char* argv[])
{
    return EventCore::EntryPoint::MainFunction(argc, argv);
}

namespace EventCore {

    // see declaration of extern static Application* CreateApplication(); in Application.h
    Application* Application::sInstance = nullptr;

    Application::~Application()
    {
    }

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
            {
                OnUpdate();
            }
            else
            {
                return;
            }

            for (auto* producer : mEventProducers)
            {
                if (mIsRunning)
                {
                    producer->EventProducerOnUpdate();
                }
                else
                {
                    return;
                }
            }

            if (mIsRunning)
            {
                mEventQueue.PublishEvents();
            }
            else
            {
                return;
            }
        }
    }

    void Application::OnConsoleSignal(ConsoleSignal sig)
    {
        LOGF_CRITICAL("Signal: {}", sig);
        Shutdown(0);
    }

    int EntryPoint::MainFunction(int argc, char* argv[])
    {
        std::filesystem::path thisBinaryPath = argv[0];
        const std::string thisBinaryName = thisBinaryPath.filename().replace_extension("").string();
    
        Application* instance = CreateApplication();
        Application::sInstance = instance;
        instance->mBinaryName = thisBinaryName;

        LOG_WARN("Initializing application...");
        START_PROFILE("App_Init", thisBinaryName);
        instance->Init();
        END_PROFILE;
        
        LOG_WARN("Entering run loop of application...");
        START_PROFILE("App_Run", thisBinaryName);
        instance->Run();
        END_PROFILE;
        
        int exitCode = instance->mExitCode;
        LOG_WARN("Destroying application instance...");
        delete instance;
        
        LOGF_WARN("Exiting with code: {}", exitCode);
        return exitCode;
    }
        
}