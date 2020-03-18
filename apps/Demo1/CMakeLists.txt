cmake_minimum_required (VERSION 3.15)

# Add source to this project's executable.
include_directories(${CMAKE_SOURCE_DIR}/libs)
link_directories(${CMAKE_SOURCE_DIR}/libs)

set (APP_EXE Demo1)
file (GLOB_RECURSE Demo1_src "*.cpp")
add_executable (${APP_EXE} ${Demo1_src})
target_link_libraries(${APP_EXE}
					  EventCoreLib)