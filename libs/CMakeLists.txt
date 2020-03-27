cmake_minimum_required (VERSION 3.15)

find_library (PROTOBUF_LIB
              NAMES libprotobuf.lib
              PATHS "C:/Dev/protobuf/lib"
              PATH_SUFFIXES "${CMAKE_BUILD_TYPE}"
              NO_DEFAULT_PATH
              )

set (LIB_NAME "EventCoreLib")
include_directories(${CMAKE_CURRENT_LIST_DIR} ${SPDLOG_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR})

file (GLOB_RECURSE CPP_SRC "*.cpp")
list (FILTER CPP_SRC EXCLUDE REGEX "^.+pch.cpp$")
file (GLOB_RECURSE PROTO_SRC "*.pb.cc")
ADD_MSVC_PRECOMPILED_HEADER("pch.h" "pch.cpp" CPP_SRC)
add_library(${LIB_NAME} STATIC ${PROTO_SRC} ${CPP_SRC})
target_link_libraries(${LIB_NAME} ws2_32.lib ${PROTOBUF_LIB})
set_target_properties (${LIB_NAME} PROPERTIES LIB_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory ("Core")
add_subdirectory ("TCP")
add_subdirectory ("Proto")