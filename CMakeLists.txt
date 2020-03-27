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

MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
    
    SET(Sources ${${SourcesVar}})

    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledBasename}.h\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    SET_SOURCE_FILES_PROPERTIES(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledBasename}.h\" /FI\"${PrecompiledBasename}.h\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  
    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

# Include sub-projects.
add_subdirectory ("libs")
add_subdirectory ("apps")