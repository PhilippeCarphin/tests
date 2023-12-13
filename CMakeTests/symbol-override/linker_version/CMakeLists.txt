cmake_minimum_required(VERSION 3.16)

project(symbol-override C Fortran)

option(USE_OVERRIDES "Use rpnphy override code" OFF)
option(WITH_SHADES "Use rpnshades library" OFF)

# RPNPHY
add_library(rpnphy rpnphy.c)

# RPNPHY-OVERRIDES
add_library(rpnphy-override rpnphy-override.c)

# GEMDYN
add_library(gemdyn gemdyn.c)
if(USE_OVERRIDES)
    # We need rpnphy-override to appear before rpnphy in gemdyn's link libraries but ...
    target_link_libraries(gemdyn PRIVATE rpnphy-override)
endif()
target_link_libraries(gemdyn PRIVATE rpnphy)

# RPNSHADES
add_library(rpnshades rpnshades.c)
target_link_libraries(rpnshades PRIVATE rpnphy)

# MAIN
add_executable(main main.c)
if(WITH_SHADES)
    target_compile_definitions(main PRIVATE WITH_SHADES)
    target_link_libraries(main PRIVATE rpnshades)
endif()
# ... but this is not enough because we still need gemdyn to appear before
# any other library that may link transitively with rpnphy.
target_link_libraries(main PRIVATE gemdyn)
if(USE_OVERRIDES AND NOT BUILD_SHARED_LIBS)
    # ... and if we need to add this, it's bad.
    target_link_options(main PRIVATE -Wl,--allow-multiple-definition)
endif()

include(CTest)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
add_test(NAME main COMMAND $<TARGET_FILE:main>)
add_dependencies(check main)
