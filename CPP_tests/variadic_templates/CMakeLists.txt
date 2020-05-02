cmake_minimum_required(VERSION 3.10)

project(Variadic_Templates)
set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp)

add_custom_target(check COMMAND ./main)
add_dependencies(check main)