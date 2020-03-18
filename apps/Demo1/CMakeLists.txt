cmake_minimum_required (VERSION 3.15)

# Add source to this project's executable.
include_directories(${CMAKE_SOURCE_DIR}/libs)
link_directories(${CMAKE_SOURCE_DIR}/libs)

set (APP_EXE Demo1)
add_executable (${APP_EXE} "Demo1.cpp" "Demo1.h")
target_link_libraries(${APP_EXE}
					  EventCoreLib)