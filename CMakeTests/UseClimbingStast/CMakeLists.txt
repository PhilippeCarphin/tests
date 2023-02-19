cmake_minimum_required(VERSION 3.20)

project(useclimb C Fortran)

find_package(climbingstats REQUIRED)

add_executable(climbingstuff main.c)
target_link_libraries(climbingstuff PRIVATE climbingstats::climbingstats)
