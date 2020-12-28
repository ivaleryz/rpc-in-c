cmake_minimum_required(VERSION 3.15)

project(network C)

set(C_STANDARD 11)

include(cmake/CompilerWarnings.cmake)
add_library(${PROJECT_NAME}_project_warnings INTERFACE)
set_project_warnings(${PROJECT_NAME}_project_warnings)

include(cmake/EnableTests.cmake)
include(cmake/BuildType.cmake)

include(cmake/Sanitizers.cmake)
add_library(${PROJECT_NAME}_sanitizers INTERFACE)
set_sanitizers(${PROJECT_NAME}_sanitizers)

include(cmake/Install.cmake)

add_subdirectory(src)