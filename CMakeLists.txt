cmake_minimum_required(VERSION 3.15)

project(rpc C)

set(C_STANDARD 11)

include(cmake/CompilerWarnings.cmake)
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

include(cmake/EnableTests.cmake)
include(cmake/BuildType.cmake)

include(cmake/Sanitizers.cmake)
add_library(sanitizers INTERFACE)
set_sanitizers(sanitizers)

add_library(rpc)
add_library(net::rpc ALIAS rpc)

target_sources(rpc PRIVATE
    src/rpc.c
)

target_include_directories(rpc PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(rpc
    PRIVATE project_warnings sanitizers
)