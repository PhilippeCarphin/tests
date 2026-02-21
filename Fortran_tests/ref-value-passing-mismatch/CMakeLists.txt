cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

add_library(func func.f90)
add_executable(main main.c)
target_link_libraries(main PUBLIC func)

include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_test(NAME run COMMAND $<TARGET_FILE:main>)
add_dependencies(check main)

