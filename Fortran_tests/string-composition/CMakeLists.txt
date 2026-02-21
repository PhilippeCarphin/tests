cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

add_executable(main main.f90)
add_executable(mainc main.c)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
add_dependencies(check main mainc)
add_test(NAME main COMMAND $<TARGET_FILE:main>)
add_test(NAME mainc COMMAND $<TARGET_FILE:mainc>)

