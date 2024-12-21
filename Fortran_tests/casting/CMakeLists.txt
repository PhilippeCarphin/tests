cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

add_executable(main main.F90)
# target_compile_options(main PRIVATE -check all,noarg_temp_created,nooutput_conversion,noshape,nobounds -debug-parameters all)
