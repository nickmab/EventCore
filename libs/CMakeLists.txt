cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (LIB_NAME "EventCoreLib")

set (THIS_DIR ${CMAKE_CURRENT_LIST_DIR})

find_library (PROTOBUF_LIB
              NAMES libprotobuf.lib
              PATHS "C:/Dev/protobuf/lib"
              PATH_SUFFIXES "${CMAKE_BUILD_TYPE}"
              NO_DEFAULT_PATH
              )

MESSAGE (STATUS ${PROTOBUF_LIBS})

include_directories(${THIS_DIR} "${CMAKE_SOURCE_DIR}/vendor/spdlog/include" "C:/Dev/protobuf/include")

file (GLOB_RECURSE ALL_SRC "*.cpp" "*.cc")
add_library(${LIB_NAME} STATIC ${ALL_SRC})
# target_link_libraries(${LIB_NAME} ws2_32.lib)
target_link_libraries(${LIB_NAME} ws2_32.lib ${PROTOBUF_LIB})
set_target_properties (${LIB_NAME} PROPERTIES LIB_ROOT_DIR ${THIS_DIR})

add_subdirectory ("Core")
add_subdirectory ("TCP")
add_subdirectory ("Proto")