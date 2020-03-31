cmake_minimum_required (VERSION 3.15)

set (APP_NAME EventProfiler)
file (GLOB_RECURSE APP_SRC "*.cpp")
add_executable (${APP_NAME} ${APP_SRC})

include_directories(${EVENTCORELIB_ROOT_DIR} 
                    ${SPDLOG_INCLUDE_DIR} 
                    ${TCLAP_INCLUDE_DIR}
                    ${PROTOBUF_INCLUDE_DIR})

target_link_libraries(${APP_NAME} EventCoreLib)
