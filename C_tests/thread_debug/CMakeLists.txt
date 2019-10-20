cmake_minimum_required(VERSION 3.15)
project(thread_debug C)

set(CMAKE_C_STANDARD 99)

add_executable(thread_debug main.c)
# find_package(pthread REQUIRED)
target_link_libraries(thread_debug PRIVATE pthread)