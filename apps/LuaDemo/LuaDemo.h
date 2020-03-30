#pragma once

#include <Core/Application.h>
#include <Lua/LuaEngine.h>

using namespace EventCore;

class LuaDemo: public Application
{
    LuaEngine mEngine;
    
    virtual void Init() override;
    virtual void OnUpdate() override;
};

Application* CreateApplication();