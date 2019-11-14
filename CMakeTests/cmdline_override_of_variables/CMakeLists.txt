project(test C)

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
set(variable cmakelists_value)
message(STATUS "variable = ${variable}")
option(option "this options explanation" cmakelists_value)
message(STATUS "option = ${option_name}")
add_executable(main main.c)
