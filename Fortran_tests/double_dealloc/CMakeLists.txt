cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

add_executable(main main.f90)
target_compile_options(main PRIVATE -traceback)
