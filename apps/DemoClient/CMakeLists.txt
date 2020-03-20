cmake_minimum_required (VERSION 3.15)

set (APP_EXE DemoClient)
file (GLOB_RECURSE APP_SRC "*.cpp")
add_executable (${APP_EXE} ${APP_SRC})

get_target_property(EventCoreLib_LIB_ROOT_DIR EventCoreLib LIB_ROOT_DIR)
include_directories("${EventCoreLib_LIB_ROOT_DIR}")
link_directories("${EventCoreLib_LIB_ROOT_DIR}")

target_link_libraries(${APP_EXE} EventCoreLib)