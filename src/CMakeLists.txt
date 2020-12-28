add_library(network)
add_library(network::network ALIAS network)

file(GLOB SOURCES network/*.c)
target_sources(network
    PRIVATE ${SOURCES}
)

target_include_directories(network
    PUBLIC ${${PROJECT_NAME}_SOURCE_DIR}/include/network
    PRIVATE ${${PROJECT_NAME}_SOURCE_DIR}/src/internal
)

target_link_libraries(network
    PRIVATE ${PROJECT_NAME}_project_warnings
            ${PROJECT_NAME}_sanitizers
)

set_target_properties(network
  PROPERTIES
    OUTPUT_NAME "network"
    PUBLIC_HEADER 
        ${${PROJECT_NAME}_SOURCE_DIR}/include/network/network.h
  )

install(
    TARGETS network
    ARCHIVE
        DESTINATION ${INSTALL_LIBDIR}
        COMPONENT lib
    RUNTIME
        DESTINATION ${INSTALL_BINDIR}
        COMPONENT bin
    LIBRARY
        DESTINATION ${INSTALL_LIBDIR}
        COMPONENT lib
    PUBLIC_HEADER
        DESTINATION ${INSTALL_INCLUDEDIR}/network
        COMPONENT dev
)
