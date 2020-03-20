cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (LIB_NAME "EventCoreLib")

set (THIS_DIR ${CMAKE_CURRENT_LIST_DIR})
include_directories(${THIS_DIR})

file (GLOB_RECURSE ALL_SRC "*.cpp")
add_library(${LIB_NAME} STATIC ${ALL_SRC})
target_link_libraries(${LIB_NAME} ws2_32.lib)
set_target_properties (${LIB_NAME} PROPERTIES LIB_ROOT_DIR ${THIS_DIR})