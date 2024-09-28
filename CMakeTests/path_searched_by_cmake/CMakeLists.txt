cmake_minimum_required(VERSION 3.16)

project(test)

set(variable value)

message(STATUS "variable=${variable}")

find_package(dummy_project REQUIRED)
