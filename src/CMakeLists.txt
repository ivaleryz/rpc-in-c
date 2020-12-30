add_subdirectory(network)
add_subdirectory(serialization)

add_library(rpc)
add_library(net::rpc ALIAS rpc)

file(GLOB SOURCES crpc/*.c)
target_sources(rpc 
    PRIVATE ${SOURCES}
)
target_include_directories(rpc 
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/internal
)

target_link_libraries(rpc
    PRIVATE ${PROJECT_NAME}_project_warnings ${PROJECT_NAME}_sanitizers net::stream network::network
)
