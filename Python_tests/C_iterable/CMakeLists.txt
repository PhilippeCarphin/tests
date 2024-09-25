cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

find_package(Python 3 REQUIRED Development)
Python_add_library(iteration MODULE module.c)


include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
add_dependencies(check iteration)
add_test(NAME try COMMAND bash -c "PYTHONPATH=${CMAKE_BINARY_DIR} python3 ${CMAKE_SOURCE_DIR}/test.py")

