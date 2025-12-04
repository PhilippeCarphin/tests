cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

find_package(OpenMP REQUIRED)

add_executable(main main.c)
target_link_libraries(main PRIVATE OpenMP::OpenMP_C)
