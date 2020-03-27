#include <pch.h>

#include "MathClient.h"

namespace EventCore {
    Application* CreateApplication()
    {
        return new ::MathClient();
    }
}

using namespace EventCore;

void MathClient::Init()
{
    mTCPClient.reset(new TCPClient(ProtoParser::Protocol::MathProto));
    RegisterEventProducer(mTCPClient.get());

    mTickEventProducer.reset(new TickEventProducer(1000));
    RegisterEventProducer(mTickEventProducer.get());

    mRouter.reset(new QAndARouter());
    RegisterEventConsumer(mRouter.get());

    mQuestionGen.reset(new QuestionGenerator(*mRouter));
    RegisterEventConsumer(mQuestionGen.get());

    if (!mTCPClient->Init())
    {
        LOG_CRITICAL("Could not initialize client; shutting down.");
        Shutdown(1);
    }
}

void MathClient::OnUpdate()
{
    if (!mTCPClient->OnUpdate())
    {
        LOG_CRITICAL("Encountered some kind of error; shutting down.");
        Shutdown(1);
    }
}

void MathClient::SendQuestion(const ProtoMsgVariant& msg)
{
    if (!mTCPClient->QueueOutgoingMessage(msg))
    {
        LOGF_CRITICAL("Unable to queue outgoing message: {}", 
            std::visit([](const auto& arg) -> std::string { return arg.DebugString(); },
                msg));
        Shutdown(1);
    }
}