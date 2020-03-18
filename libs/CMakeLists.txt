cmake_minimum_required (VERSION 3.15)
include_directories(${CMAKE_SOURCE_DIR}/libs)
file (GLOB_RECURSE Core_src "*.cpp")
add_library(EventCoreLib STATIC ${Core_src})