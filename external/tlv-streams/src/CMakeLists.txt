add_library(stream)
add_library(net::stream ALIAS stream)

target_sources(stream PRIVATE
    stream.c
)

target_include_directories(stream PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(stream
    PRIVATE ${PROJECT_NAME}_project_warnings ${PROJECT_NAME}_sanitizers
)

set_target_properties(stream
  PROPERTIES
    OUTPUT_NAME "stream"
    PUBLIC_HEADER 
        ${CMAKE_SOURCE_DIR}/include/stream.h
  )

install(
    TARGETS stream
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
        DESTINATION ${INSTALL_INCLUDEDIR}/stream
        COMPONENT dev
)
