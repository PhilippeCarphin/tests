cmake_minimum_required(VERSION 3.20)

project(OpenMP-Hello-World C Fortran)

find_package(OpenMP REQUIRED)

add_executable(main main.c)

target_link_libraries(main PRIVATE OpenMP::OpenMP_C)

add_executable(fmain main.F90)
target_link_libraries(fmain PRIVATE OpenMP::OpenMP_Fortran)

