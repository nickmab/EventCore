#include <pch.h>

#include "LuaDemo.h"

namespace EventCore {
    Application* CreateApplication()
    {
        return new ::LuaDemo();
    }
}

using namespace EventCore;

void LuaDemo::Init()
{
}

void LuaDemo::OnUpdate()
{
}
