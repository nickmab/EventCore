cmake_minimum_required (VERSION 3.15)

get_target_property(EVENTCORELIB_ROOT_DIR EventCoreLib ROOT_DIR)

add_subdirectory ("EventProfiler")
add_subdirectory ("LuaDemo")
add_subdirectory ("MathDemo")
