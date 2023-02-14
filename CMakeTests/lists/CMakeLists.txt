cmake_minimum_required(VERSION 3.10)


file(GLOB FORTRAN_FILES files/*.f90 files/*.F90)

file(GLOB C_FILES files/*.c)

list(APPEND FORTRAN_FILES ${C_FILES})

foreach(f IN ITEMS ${FORTRAN_FILES})
    message(STATUS "file = ${f}")
endforeach()

message(STATUS "======================================================")
set(glob_expr "files/*.f90;files/*.F90")
if(ADD_FILES)
    set(glob_expr "${glob_expr};files/*.c")
endif()

file(GLOB THE_FILES ${glob_expr})

message(STATUS "THE_FILES=${THE_FILES}")
