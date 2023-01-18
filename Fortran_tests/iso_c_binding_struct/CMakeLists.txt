cmake_minimum_required(VERSION 3.12)

project(struct_iso_c_binding C Fortran)

add_executable(main tgrid.F90 tgrid.c main.F90)


