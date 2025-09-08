cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

add_executable(main main.f90 func.f90 func.c)
target_compile_options(main PRIVATE -fno-range-check)

include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_test(NAME run COMMAND $<TARGET_FILE:main>)
add_dependencies(check main)

