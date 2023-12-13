cmake_minimum_required(VERSION 3.16)

project(symbol-override C Fortran)

option(USE_OVERRIDES "Use rpnphy override code" TRUE)
option(WITH_SHADES "Use rpnshades library" FALSE)
set(METHOD OVERRIDE CACHE STRING "Decide between the override (sketchy) and the define (non-sketchy)")

add_library(rpnphy rpnphy.c)
add_library(gemdyn gemdyn.c)
add_library(rpnshades rpnshades.c)
target_link_libraries(rpnshades PRIVATE rpnphy)

if(${METHOD} STREQUAL OVERRIDE)

    add_library(rpnphy-override rpnphy-override.c)

    if(USE_OVERRIDES)
        target_link_libraries(gemdyn PRIVATE rpnphy-override rpnphy)
    else()
        target_link_libraries(gemdyn PRIVATE rpnphy)
    endif()

elseif(${METHOD} STREQUAL DEFINES)

    add_library(rpnphy-custom rpnphy-custom.c)

    target_link_libraries(gemdyn PRIVATE rpnphy-custom rpnphy)
    if(USE_OVERRIDES)
        target_compile_definitions(gemdyn PRIVATE USE_OVERRIDES)
    endif()

else()
    message(FATAL_ERROR "Value of METHOD must be OVERRIDE or DEFINES")
endif()

add_executable(main main.c)
target_link_libraries(main PRIVATE rpnphy-override)
if(WITH_SHADES)
    target_compile_definitions(main PRIVATE WITH_SHADES)
    target_link_libraries(main PRIVATE rpnshades)
endif()
target_link_libraries(main PRIVATE gemdyn)
if(${METHOD} STREQUAL OVERRIDE AND USE_OVERRIDES AND NOT BUILD_SHARED_LIBS)
    target_link_options(main PRIVATE -Wl,--allow-multiple-definition)
endif()

include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

add_test(NAME main COMMAND $<TARGET_FILE:main>)
add_dependencies(check main)
