#include "pch.h"

#include "LuaEngine.h"

namespace EventCore {

    LuaEngine::LuaEngine()
    {
		{
			lua_State* L = luaL_newstate();
			luaL_dostring(L, "x = 47");
			lua_getglobal(L, "x");
			lua_Number x = lua_tonumber(L, 1);
			LOGF_WARN("lua says x = {}", (int)x);
			lua_close(L);
		}
    }

}