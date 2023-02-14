cmake_minimum_required(VERSION 3.12)

project(struct_iso_c_binding C Fortran)

# list(APPEND CMAKE_MODULE_PATH /home/phc001/Repositories/gitlab.science.gc.ca/RPN-SI/cmake_rpn/modules)

# include(ec_init)
set(CMAKE_Fortran_PREPROCESS TRUE)

add_executable(main grid.f90 grid.c main.f90 tgrid_mod.f90)

add_custom_target(
    check
    COMMAND
        ${CMAKE_BINARY_DIR}/main
    DEPENDS
        main
)


