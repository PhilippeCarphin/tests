cmake_minimum_required (VERSION 2.6)
project (Tutorial)

SET(PYTHON_VERSION_MAJOR_DOT_MINOR 3.4)
SET(PYTHON_VERSION_MAJOR_MINOR 34)
SET(Python_ADDITIONAL_VERSIONS ${PYTHON_VERSION_MAJOR_DOT_MINOR})
FIND_PACKAGE(PythonLibs ${PYTHON_VERSION_MAJOR_DOT_MINOR} REQUIRED)

find_package(Boost REQUIRED COMPONENTS system python)

add_library(pygreeter SHARED greeter.cpp)

target_link_libraries(pygreeter ${Boost_LIBRARIES} ${PROJECT_NAME})
