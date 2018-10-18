cmake_minimum_required (VERSION 2.6)

# Defines the name of the project
project (Tutorial)

# This CMakeLists.txt demonstrates that you can have files in different
# directories without necessarily having to make a CMakeLists.txt file in the
# subdirectories

# What seems to affect the choice of one-file-per-directory versus only-one-file would be for things one-file for things that are indivisible like a
# Root
# ├── CMakeLists.txt
# ├── include
# │   └── say_hello.h
# └── src
#     ├── main.cpp
#     └── say_hello.cpp

file(GLOB SAY_HELLO_SRC "src/*.cpp")
add_executable(Tuto.out ${SAY_HELLO_SRC})

target_include_directories(Tuto.out PUBLIC ./include)
