cmake_minimum_required(VERSION 3.16)

project(hybrid C Fortran)

add_executable(main main.c subroutines.F90)

add_executable(fmain main.F90)
