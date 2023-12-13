cmake_minimum_required(VERSION 3.16)

project(dlopen_test C Fortran)

# Create a "plugin": arithmetic_mean
add_library(arithmetic_mean MODULE arithmetic_mean.c)
set_target_properties(arithmetic_mean PROPERTIES PREFIX "")

# Create a "plugin": geometric_mean
add_library(geometric_mean MODULE geometric_mean.c)
set_target_properties(geometric_mean PROPERTIES PREFIX "")
target_link_libraries(geometric_mean PRIVATE m)

# Create an executable that will load one of these plugins
add_executable(main main.c)
target_link_libraries(main PRIVATE dl)
