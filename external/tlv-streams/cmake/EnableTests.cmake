option(ENABLE_TESTS "Enable testing" ON)
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(${${PROJECT_NAME}_SOURCE_DIR}/tests)
    
endif()