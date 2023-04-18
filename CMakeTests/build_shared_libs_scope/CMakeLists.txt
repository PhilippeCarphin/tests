cmake_minimum_required(VERSION 3.20)

project(scope_test)

include(CMakePrintHelpers)

cmake_print_variables(BUILD_SHARED_LIBS)
set(subdir_SHARED_LIBS YES)
set(parent_var "parent_var_value")
set(parent_list A B C)
add_subdirectory(subdir)
cmake_print_variables(parent_var)
cmake_print_variables(subdir_var)
cmake_print_variables(parent_list)
cmake_print_variables(BUILD_SHARED_LIBS)
