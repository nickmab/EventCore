cmake_minimum_required (VERSION 3.15)
set (LIB_NAME "EventCoreLib")

set (THIS_DIR ${CMAKE_CURRENT_LIST_DIR})
include_directories(${THIS_DIR})

file (GLOB_RECURSE ALL_SRC "*.cpp")
add_library(${LIB_NAME} STATIC ${ALL_SRC})

set_target_properties (${LIB_NAME} PROPERTIES LIB_ROOT_DIR ${THIS_DIR})