#include <pch.h>

#include "LuaDemo.h"

#include <tclap/CmdLine.h>

namespace EventCore {
    Application* CreateApplication(int argc, char* argv[])
    {
        return new ::LuaDemo(argc, argv);
    }
}

using namespace EventCore;

LuaDemo::LuaDemo(int argc, char* argv[])
{
	std::string filename;
	try 
	{
		TCLAP::CmdLine cmd("Lua script runner", ' ', "0.1");
		
		// filename arg; required, no default value.
		TCLAP::ValueArg<std::string> filenameArg("f", "filename", "Lua script to run", true, "", "filename:string");

		cmd.add(filenameArg);
		cmd.parse(argc, argv);

		filename = filenameArg.getValue();
	}
	catch (TCLAP::ArgException & e)
	{
		LOGF_CRITICAL("Error parsing cmd line args. Error: {} Argument: {}",
			e.error(), e.argId());
		Shutdown(1);
	}

	mEngine.reset(new LuaEngine(filename.c_str()));
}

void LuaDemo::Init()
{
	// By now our script will have run. That's it.
	Shutdown(0);
}

void LuaDemo::OnUpdate()
{
}
