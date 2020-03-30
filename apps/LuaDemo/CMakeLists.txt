cmake_minimum_required (VERSION 3.15)

set (APP_NAME LuaDemo)
file (GLOB_RECURSE APP_SRC "*.cpp")
add_executable (${APP_NAME} ${APP_SRC})

add_custom_command(TARGET ${APP_NAME} 
                   PRE_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E copy "${LUA_LIB_DIR}/lua_dynamic_lib.dll" ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${EVENTCORELIB_ROOT_DIR} 
                    ${SPDLOG_INCLUDE_DIR} 
                    ${PROTOBUF_INCLUDE_DIR}
                    ${LUA_INCLUDE_DIR})

target_link_libraries(${APP_NAME} EventCoreLib)
