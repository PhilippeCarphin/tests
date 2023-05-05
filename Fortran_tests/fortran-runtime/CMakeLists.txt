cmake_minimum_required(VERSION 3.20)

project(fortran_io C Fortran)

add_library(fprint_string STATIC print_string.f90)
add_library(cprint_string STATIC print_string.c)

add_executable(mainlc main.c)
add_executable(mainlf main.c)
target_link_libraries(mainlf PRIVATE fprint_string)
target_link_libraries(mainlc PRIVATE cprint_string)

