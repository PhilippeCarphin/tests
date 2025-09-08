cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

add_executable(main maybe_in_maybe_out.c interface.f90 main.f90)

include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
add_dependencies(check main)

add_test(NAME main COMMAND $<TARGET_FILE:main>)
