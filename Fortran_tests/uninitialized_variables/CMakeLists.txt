cmake_minimum_required(VERSION 3.20)


list(APPEND CMAKE_MODULE_PATH $ENV{EC_CMAKE_MODULE_PATH})

include(ec_init)

project(X C Fortran)

include(ec_compiler_presets)

add_executable(main main.f90)

include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

add_test(NAME run COMMAND $<TARGET_FILE:main>)
add_dependencies(check main)
