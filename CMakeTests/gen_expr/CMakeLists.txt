cmake_minimum_required(VERSION 3.10)

project(gen_expr C)

add_executable(main main.c)

message(STATUS "LIB_CPL=${LIB_CPL}")
target_compile_definitions(main PUBLIC $<IF:$<STREQUAL:${LIB_CPL},>,LIB_CPL=\"EMPTY\",LIB_CPL=\"${LIB_CPL}\">)

add_custom_target(check
    COMMAND ./main
    DEPENDS main
)
