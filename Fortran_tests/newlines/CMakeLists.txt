cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

add_executable(good good.f90)

add_executable(bad bad.f90)

add_executable(explanation explanation.f90)

add_executable(print-without-newline print-without-newline.f90)

add_library(print print_string.c)

target_link_libraries(good print)

target_link_libraries(bad print)
