SET(CMAKE_FORTRAN_COMPILER /usr/local/bin/gfortran)
ENABLE_LANGUAGE(Fortran)
PROJECT(calling_convention CXX C FORTRAN)

add_library(frmn SHARED frmn.f)
add_library(rmn SHARED rmn.c)
target_link_libraries(rmn PRIVATE frmn)
target_compile_options(rmn PRIVATE -std=c99)
target_compile_options(rmn PUBLIC -O3)

add_executable(main main.cpp)
target_compile_options(main PUBLIC -O3)
target_link_libraries(main PRIVATE rmn)
target_link_libraries(main PRIVATE frmn)
