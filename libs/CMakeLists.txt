cmake_minimum_required (VERSION 3.15)

# Include sub-projects.
add_subdirectory ("Core")

add_library(EventCoreLib STATIC
			Core/Application.cpp)