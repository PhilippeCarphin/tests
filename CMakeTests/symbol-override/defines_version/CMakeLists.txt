cmake_minimum_required(VERSION 3.16)

project(function-override C Fortran)

option(USE_OVERRIDES "Use rpnphy override code" TRUE)
option(WITH_SHADES "Use rpnshades library" FALSE)

# RPNPHY
add_library(rpnphy rpnphy.c)
if(USE_OVERRIDES)
    target_compile_definitions(rpnphy PRIVATE USE_OVERRIDES)
endif()

# GEMDYN
add_library(gemdyn gemdyn.c)
target_link_libraries(gemdyn PRIVATE rpnphy)

# RPNSHADES
add_library(rpnshades rpnshades.c)
target_link_libraries(rpnshades PRIVATE rpnphy)

# MAIN
add_executable(main main.c)
target_link_libraries(main PRIVATE gemdyn)
if(WITH_SHADES)
    target_compile_definitions(main PRIVATE WITH_SHADES)
    target_link_libraries(main PRIVATE rpnshades)
endif()


include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
add_test(NAME main COMMAND $<TARGET_FILE:main>)
add_dependencies(check main)
