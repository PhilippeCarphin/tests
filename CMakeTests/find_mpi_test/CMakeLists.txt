cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH $ENV{HOME}/Repositories/gitlab.science.gc.ca/RPN-SI/cmake_rpn/modules)
include(ec_init)

project(find_mpi_test C Fortran)

include(ec_compiler_presets)

find_package(MPI REQUIRED COMPONENTS)
