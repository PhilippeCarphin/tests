cmake_minimum_required(VERSION 3.20)

project(version_links C)

add_library(mylib SHARED lib.c)
set_target_properties(mylib PROPERTIES
    PUBLIC_HEADER lib.h
    VERSION 3.2.1
    SOVERSION 3.2
)

add_executable(exec exec.c)
target_link_libraries(exec PRIVATE mylib)
set_target_properties(exec PROPERTIES
    VERSION 3.2.1
)

install(TARGETS mylib exec
    # RUNTIME DESTINATION bin
    # LIBRARY DESTINATION lib
    # ARCHIVE DESTINATION lib
    # PUBLIC_HEADER DESTINATION include
)
