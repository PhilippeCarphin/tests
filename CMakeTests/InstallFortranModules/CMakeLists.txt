cmake_minimum_required(VERSION 3.10)


project(install_modules_glob Fortran)

add_custom_target(make_mods ALL
    COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/a.mod
    COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/b.mod
    COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/c.smod
    COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/d.smod
)
