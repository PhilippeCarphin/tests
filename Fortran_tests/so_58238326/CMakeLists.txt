cmake_minimum_required(VERSION 3.7.2)
project(Mcve LANGUAGES C CXX Fortran)

add_library(FortLib STATIC fort.f90)
target_include_directories(FortLib INTERFACE ${CMAKE_CURRENT_LIST_DIR})

add_library(LibWithMain STATIC main.cpp)

add_executable(App app.cpp)
target_link_libraries(App PRIVATE LibWithMain FortLib)

