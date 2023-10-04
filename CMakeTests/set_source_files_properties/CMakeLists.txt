cmake_minimum_required(VERSION 3.20)

project(set_source_files_properties C)

add_executable(print_args main.c func.c)

target_compile_options(print_args PRIVATE -Wall)

set_source_files_properties(func.c PROPERTIES COMPILE_OPTIONS -Werror=implicit-function-declaration)
