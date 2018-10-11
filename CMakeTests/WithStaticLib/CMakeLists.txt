cmake_minimum_required (VERSION 2.6)

# Defines the name of the project
project (Tutorial)

# Defines a library to build with filename libsay_hello.a and source say_hello.cpp
add_library(say_hello say_hello.cpp)

# Defines an executable to build with filename Tuto and source main.cpp
add_executable(Tuto main.cpp)

# Causes the Tuto executable to be built with "-lsay_hello"
target_link_libraries(Tuto say_hello)
