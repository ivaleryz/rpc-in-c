find_package(Threads REQUIRED)

add_executable(test_udp_server_client test_udp_server_client.c)
target_link_libraries(test_udp_server_client network::network
                                ${PROJECT_NAME}_project_warnings
                                ${PROJECT_NAME}_sanitizers
                                Threads::Threads
)
add_test(
    NAME test_udp_server_client
    COMMAND test_udp_server_client
)
