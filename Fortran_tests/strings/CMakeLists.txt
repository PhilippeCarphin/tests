cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
project(Fortran_Strings Fortran C)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.f90 print_string.c)

