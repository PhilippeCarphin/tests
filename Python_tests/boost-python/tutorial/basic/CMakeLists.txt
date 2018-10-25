cmake_minimum_required (VERSION 2.6)
project (Tutorial)

find_package(PythonLibs ${PY_VERSION} REQUIRED)
find_package(Boost REQUIRED COMPONENTS system python)

add_library(pygreeter SHARED greeter.cpp)

target_link_libraries(pygreeter ${Boost_LIBRARIES} ${PROJECT_NAME})
