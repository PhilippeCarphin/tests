cmake_minimum_required(VERSION 3.10)

project(FortranBasicDemo Fortran)


file(GLOB FORTRAN_FILES RELATIVE ${CMAKE_SOURCE_DIR} *.f90)
message(STATUS "FORTRAN_FILES = ${FORTRAN_FILES}")
add_executable(main ${FORTRAN_FILES})
# add_library(basicdemo basicdemo.f90)
