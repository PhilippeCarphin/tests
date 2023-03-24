cmake_minimum_required(VERSION 3.20)

project(transitive_static_dep C)

add_library(multiply multiply.c)
target_include_directories(multiply INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(multiply PROPERTIES PUBLIC_HEADER multiply.h)

add_library(dotproduct dotproduct.c)
target_include_directories(dotproduct INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(dotproduct PROPERTIES PUBLIC_HEADER dotproduct.h)
target_link_libraries(dotproduct PRIVATE multiply)

add_executable(main main.c)
target_link_libraries(main PRIVATE dotproduct)

include(CMakePrintHelpers)
cmake_print_properties(TARGETS multiply dotproduct main
    PROPERTIES
        INTERFACE_LINK_LIBRARIES
        INTERFACE_INCLUDE_DIRECTORIES
        LINK_LIBRARIES
)

