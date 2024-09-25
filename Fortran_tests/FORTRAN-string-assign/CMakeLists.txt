cmake_minimum_required(VERSION 3.16)
project(FORTRAN_STRINGS C Fortran)

add_library(grid grid.h grid_mod.f90 tgrid_mod.f90 grid.c)

add_executable(main main.f90)
target_link_libraries(main grid)

include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)


add_test(NAME run COMMAND $<TARGET_FILE:main>)
add_dependencies(check main)
