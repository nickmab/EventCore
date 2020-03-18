cmake_minimum_required (VERSION 3.15)

set (APP_EXE Demo1)
file (GLOB_RECURSE Demo1_src "*.cpp")
add_executable (${APP_EXE} ${Demo1_src})

get_target_property(EventCoreLib_LIB_ROOT_DIR EventCoreLib LIB_ROOT_DIR)
include_directories("${EventCoreLib_LIB_ROOT_DIR}")
link_directories("${EventCoreLib_LIB_ROOT_DIR}")

target_link_libraries(${APP_EXE} EventCoreLib)