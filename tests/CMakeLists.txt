add_executable(test_stub test_stub.c)
target_link_libraries(test_stub network::network
                                ${PROJECT_NAME}_project_warnings
                                ${PROJECT_NAME}_sanitizers
)
add_test(
    NAME test_stub
    COMMAND test_stub
)
