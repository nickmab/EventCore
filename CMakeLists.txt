# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project ("EventCore")

# Include sub-projects.
add_subdirectory ("libs")
add_subdirectory ("apps")
