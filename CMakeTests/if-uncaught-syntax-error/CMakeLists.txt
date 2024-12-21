cmake_minimum_required(VERSION 3.10)

project(X C Fortran)

#
# This test demonstrates what happens when we use a CMake syntax that doesn
# exist
#

message(STATUS "if((PHIL) OR (LAPIN COQUIN) OR (PHIL))")
if((PHIL) OR (LAPIN COQUIN) OR (PHIL))
    message(STATUS "if -> true")
else()
    message(STATUS "if -> false")
endif()

message(STATUS "if((LAPIN COQUIN) OR (PHIL))")
if((LAPIN COQUIN) OR (PHIL))
    message(STATUS "if -> true")
else()
    message(STATUS "if -> false")
endif()

message(STATUS "if((PHIL) OR (LAPIN COQUIN))")
if((PHIL) OR (LAPIN COQUIN))
    message(STATUS "if -> true")
else()
    message(STATUS "if -> false")
endif()
