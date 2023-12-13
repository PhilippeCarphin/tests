cmake_minimum_required(VERSION 3.7.2)
project(Mcve LANGUAGES C CXX Fortran)

# set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
# add_library(FortLib STATIC fort_initial.f90)

add_library(FortLib STATIC fort.f90)
target_include_directories(FortLib INTERFACE ${CMAKE_CURRENT_LIST_DIR})
# By using iso_c_binding and making fortfunc be bind(C),
# we don't need this:
# target_compile_options(FortLib PRIVATE /names:lowercase /assume:underscore /iface:cref)

add_library(LibWithMain STATIC main.cpp)

add_executable(App app.cpp)

target_link_libraries(App PRIVATE LibWithMain FortLib)
# /usr/bin/c++ CMakeFiles/App.dir/app.cpp.o -o App  libLibWithMain.a libFortLib.a -lgfortran -lquadmath

# target_link_libraries(App PRIVATE FortLib LibWithMain)
# /usr/bin/c++ CMakeFiles/App.dir/app.cpp.o -o App  libFortLib.a libLibWithMain.a -lgfortran -lquadmath

