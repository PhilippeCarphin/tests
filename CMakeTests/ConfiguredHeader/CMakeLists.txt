cmake_minimum_required (VERSION 2.6)
set(Tutorial_PROGRAM_AUTHOR \"Philippe Carphin\")
set(PWD $ENV{PWD})
set(VARNAME a_var_name)
set(A_MACRO \#define)

project (Tutorial)
add_executable(Tuto.out main.cpp)

configure_file (
  "cmake_config.h.in"
  "cmake_config.h"
  )
