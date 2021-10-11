cmake_minimum_required(VERSION 3.10)

project(derek_banas_shape Fortran)

file(GLOB FORTRAN_FILES
    RELATIVE ${CMAKE_SOURCE_DIR}
    *.f90
)

add_executable(main ${FORTRAN_FILES})
