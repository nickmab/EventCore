# I'm going to apologise in advance for how badly protobuf is handled
# in this project...I am an amateur obviously.

cmake_minimum_required (VERSION 3.15)

project ("EventCore")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT WIN32)
    message (FATAL_ERROR "Project currently only supports Windows.")
endif ()

if(MSVC)
	# Use multiple processors when building
    add_compile_options(/MP)				
else()
	# add_compile_options(-W -Wall -Werror)
    message (FATAL_ERROR "Project currently only works with MSVC.")
endif()

# Header only...
set (SPDLOG_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vendor/spdlog/include")
set (TCLAP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vendor/tclap/include")

# Must already be installed somewhere...
set (PROTOBUF_INCLUDE_DIR "C:/Dev/protobuf/include")
set (PROTOBUF_LIB_DIR "C:/Dev/protobuf/lib/${CMAKE_BUILD_TYPE}")

# This we will build ourselves...
set (LUA_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vendor/lua/src")
set (LUA_LIB_DIR "${CMAKE_CURRENT_BINARY_DIR}/vendor/lua/src")

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

# See example use case in libs/CMakeLists.txt
macro (add_msvc_precompiled_header PRECOMPILED_HDR PRECOMPILED_SRC TARGET_SRC_LIST)
    
    get_filename_component (PRECOMPILED_BASENAME ${PRECOMPILED_HDR} NAME_WE)
    set (PRECOMPILED_BIN "${CMAKE_CURRENT_BINARY_DIR}/${PRECOMPILED_BASENAME}.pch")
    
    set (TARGET_SRC_LIST_EXPANDED ${${TARGET_SRC_LIST}})

    set_source_files_properties (${PRECOMPILED_SRC}
                                  PROPERTIES COMPILE_FLAGS "/Yc\"${PRECOMPILED_BASENAME}.h\" /Fp\"${PRECOMPILED_BIN}\""
                                             OBJECT_OUTPUTS "${PRECOMPILED_BIN}")
    
    set_source_files_properties (${TARGET_SRC_LIST_EXPANDED}
                                 PROPERTIES COMPILE_FLAGS "/Yu\"${PRECOMPILED_BASENAME}.h\" /FI\"${PRECOMPILED_BASENAME}.h\" /Fp\"${PRECOMPILED_BIN}\""
                                            OBJECT_DEPENDS "${PRECOMPILED_BIN}")  
    
    list (APPEND ${TARGET_SRC_LIST} ${PRECOMPILED_SRC})

endmacro (add_msvc_precompiled_header)

# It's important that we include the libs before the apps, because the libs 
# defines some variables and targets subsequently referred to by the apps.
add_subdirectory ("vendor/lua")
add_subdirectory ("libs")
add_subdirectory ("apps")