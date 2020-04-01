#include "pch.h"

#include "LuaEngine.h"

#include "Core/Application.h"

namespace EventCore {

    LuaEngine::LuaEngine(const char* filename)
    {
		lua_State* L = luaL_newstate();
		
		// surely there's a better way of doing all this...
		luaopen_base(L);
		// luaopen_bit32(L); // DEPRECATED.
		luaopen_coroutine(L);
		luaopen_debug(L);
		luaopen_io(L);
		luaopen_math(L);
		luaopen_os(L);
		luaopen_package(L);
		luaopen_string(L);
		luaopen_table(L);
		luaopen_utf8(L);
		
		if (luaL_dofile(L, filename) != LUA_OK)
		{
			LOG_ERROR(lua_tostring(L, -1));
			LOGF_CRITICAL("Error running lua script file: {} -> shutting down.", filename);
			Application::Get().Shutdown(1);
		}
		lua_close(L);
    }

}