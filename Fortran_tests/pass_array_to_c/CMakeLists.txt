cmake_minimum_required(VERSION 3.20)

project(arrays C Fortran)

add_library(cprintarray STATIC print_array.c print_array.F90)

add_executable(pass_array_to_c main.F90)
target_link_libraries(pass_array_to_c PRIVATE cprintarray)

add_executable(cprogram main.c)
target_link_libraries(cprogram PRIVATE cprintarray)

include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
add_dependencies(check pass_array_to_c cprogram)

add_test(NAME run-fortran-program COMMAND $<TARGET_FILE:pass_array_to_c>)
add_test(NAME run-c-program COMMAND $<TARGET_FILE:cprogram>)
if(${CMAKE_C_COMPILER_ID} STREQUAL Intel)
    find_library(ifport_library ifport PATHS ENV LD_LIBRARY_PATH)
    get_filename_component(icc_libdir ${ifport_library} DIRECTORY)
    set_target_properties(cprogram pass_array_to_c PROPERTIES BUILD_RPATH ${icc_libdir}  INSTALL_RPATH ${icc_libdir})
endif()
