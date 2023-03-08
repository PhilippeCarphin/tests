cmake_minimum_required(VERSION 3.20)

project(env_var_module_path C)

# This test demonstrates that CMake does not look the environment
# variable CMAKE_MODULE_PATH.
#
# Sourcing env_setup.dot sets the environment variable CMAKE_MODULE_PATH
# to a directory containing phil_func.cmake but if we comment the following
# line, we see that the include fails.
list(APPEND CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})

include(phil_func)

# add_executable(main main.c)
