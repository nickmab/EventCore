# I'm going to apologise in advance for how badly protobuf is handled
# in this project...I am an amateur obviously.

cmake_minimum_required (VERSION 3.15)

project ("EventCore")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT WIN32)
	message (FATAL_ERROR "Project currently only supports Windows.")
endif ()

set (SPDLOG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vendor/spdlog/include")
set (PROTOBUF_INCLUDE_DIR "C:/Dev/protobuf/include")

add_compile_definitions (GOOGLE_PROTOBUF_NO_THREAD_SAFETY)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	add_compile_definitions (BUILD_Debug)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
	add_compile_definitions  (BUILD_RelWithDebInfo)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	add_compile_definitions  (BUILD_Release)
else ()
	message (FATAL_ERROR "Build configuration '${CMAKE_BUILD_TYPE}' not supported.")
endif ()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Include sub-projects.
add_subdirectory ("libs")
add_subdirectory ("apps")