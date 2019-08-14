SET(CMAKE_FORTRAN_COMPILER /usr/bin/gfortran)
ENABLE_LANGUAGE(Fortran)
cmake_minimum_required(VERSION 3.0)
PROJECT(calling_convention CXX C FORTRAN)

add_library(frmn SHARED frmn.f)

add_library(rmn SHARED rmn.c)
target_link_libraries(rmn PRIVATE frmn)
target_compile_options(rmn PRIVATE -std=c99 -Wno-format -O3)

add_executable(main main.cpp)
target_compile_options(main PUBLIC -O3)
target_link_libraries(main PRIVATE rmn frmn)

add_custom_target(check COMMAND ./main)
add_dependencies(check main)
