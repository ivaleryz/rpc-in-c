add_executable(test_stream_init test_stream_init.c)
target_link_libraries(test_stream_init net::stream ${PROJECT_NAME}_project_warnings ${PROJECT_NAME}_sanitizers)
add_test(
    NAME test_stream_init
    COMMAND test_stream_init
)

add_executable(test_ser_string test_ser_string.c)
target_link_libraries(test_ser_string net::stream ${PROJECT_NAME}_project_warnings ${PROJECT_NAME}_sanitizers)
add_test(
    NAME test_ser_string
    COMMAND test_ser_string
)

add_executable(test_is_empty test_is_empty.c)
target_link_libraries(test_is_empty net::stream ${PROJECT_NAME}_project_warnings ${PROJECT_NAME}_sanitizers)
add_test(
    NAME test_is_empty
    COMMAND test_is_empty
)

add_executable(test_offset_copy test_offset_copy.c)
target_link_libraries(test_offset_copy net::stream ${PROJECT_NAME}_project_warnings ${PROJECT_NAME}_sanitizers)
add_test(
    NAME test_offset_copy
    COMMAND test_offset_copy
)

add_executable(test_checkpoint test_checkpoint.c)
target_link_libraries(test_checkpoint net::stream ${PROJECT_NAME}_project_warnings ${PROJECT_NAME}_sanitizers)
add_test(
    NAME test_checkpoint
    COMMAND test_checkpoint
)

add_executable(test_skip test_skip.c)
target_link_libraries(test_skip net::stream ${PROJECT_NAME}_project_warnings ${PROJECT_NAME}_sanitizers)
add_test(
    NAME test_skip
    COMMAND test_skip
)

add_executable(test_free test_free.c)
target_link_libraries(test_free net::stream ${PROJECT_NAME}_project_warnings ${PROJECT_NAME}_sanitizers)
add_test(
    NAME test_free
    COMMAND test_free
)
