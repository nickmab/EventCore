#pragma once

#include <Core/Application.h>
#include <Core/Events/EventQueue.h>
#include <TCP/TCPServer.h>

#include "QuestionAnswerer.h"

using namespace EventCore;

// circularity in these classes due to the SendAnswer method.
class QuestionAnswerer;

class MathServer : public Application
{
public:
    void SendAnswer(TCPSession::SessionId, const ProtoMsgVariant&);

private:
    std::unique_ptr<TCPServer> mServer{nullptr};
    std::unique_ptr<QuestionAnswerer> mAnswerer{nullptr};

    virtual void Init() override;
    virtual void OnUpdate() override;
};

Application* CreateApplication(int argc, char* argv[]);