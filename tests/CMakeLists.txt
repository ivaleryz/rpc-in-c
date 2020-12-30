find_package(Threads REQUIRED)

add_executable(test_stub test_stub.c)
target_link_libraries(test_stub network::network
                                ${PROJECT_NAME}_project_warnings
                                ${PROJECT_NAME}_sanitizers
)
add_test(
    NAME test_stub
    COMMAND test_stub
)

add_executable(test_rpc test_rpc.c)
target_link_libraries(test_rpc network::network
                                ${PROJECT_NAME}_project_warnings
                                ${PROJECT_NAME}_sanitizers
                                net::stream
                                net::rpc
                                Threads::Threads
)
target_include_directories(test_rpc
    PUBLIC ${${PROJECT_NAME}_SOURCE_DIR}/include
)
add_test(
    NAME test_rpc
    COMMAND test_rpc
)
