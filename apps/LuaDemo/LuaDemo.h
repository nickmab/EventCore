#pragma once

#include <Core/Application.h>
#include <Lua/LuaEngine.h>

using namespace EventCore;

class LuaDemo: public Application
{
public:
    LuaDemo(int argc, char* argv[]);
    
private:
    std::unique_ptr<LuaEngine> mEngine;
    
    virtual void Init() override;
    virtual void OnUpdate() override;
};

Application* CreateApplication(int argc, char* argv[]);