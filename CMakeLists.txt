# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project ("EventCore")

if (NOT WIN32)
	message (FATAL_ERROR "Project currently only supports Windows.")
endif ()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	add_compile_definitions (BUILD_Debug)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
	add_compile_definitions  (BUILD_RelWithDebInfo)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	add_compile_definitions  (BUILD_Release)
else ()
	message (FATAL_ERROR "Build configuration '${CMAKE_BUILD_TYPE}' not supported.")
endif ()

# Include sub-projects.
add_subdirectory ("libs")
add_subdirectory ("apps")