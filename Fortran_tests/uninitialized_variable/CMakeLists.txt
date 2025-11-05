cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

add_executable(main main.f90)

include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

add_test(NAME run COMMAND $<TARGET_FILE:main>)
add_dependencies(check main)
