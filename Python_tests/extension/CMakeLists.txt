cmake_minimum_required(VERSION 3.16)

project(python_extension C)

find_package(PythonLibs 3 REQUIRED)

PYTHON_ADD_MODULE(myModule myModule.c)
target_include_directories(myModule PRIVATE ${PYTHON_INCLUDE_DIRS})
