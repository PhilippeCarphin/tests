cmake_minimum_required(VERSION 3.20)

project(switch_fallthrough C)

add_executable(main main.c)

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_C_COMPILER_ID)
if(CMAKE_C_COMPILER_ID STREQUAL Intel)
    message(WARNING "The compiler ID is '${CMAKE_C_COMPILER_ID}' \
    which does not support '-Wimplicit-fallthrough' and thus \
    defeats the purpose of this test")
else()
    target_compile_options(main PRIVATE -Wimplicit-fallthrough)
endif()
