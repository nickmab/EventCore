cmake_minimum_required (VERSION 3.15)

set (SERVER_EXE MathServer)
file (GLOB_RECURSE SERVER_SRC "MathServer/*.cpp")
add_executable (${SERVER_EXE} ${SERVER_SRC})

set (CLIENT_EXE MathClient)
file (GLOB_RECURSE CLIENT_SRC "MathClient/*.cpp")
add_executable (${CLIENT_EXE} ${CLIENT_SRC})

include_directories(${EVENTCORELIB_ROOT_DIR} 
                    ${SPDLOG_INCLUDE_DIR} 
                    ${PROTOBUF_INCLUDE_DIR})

target_link_libraries(${SERVER_EXE} EventCoreLib)
target_link_libraries(${CLIENT_EXE} EventCoreLib)