cmake_minimum_required (VERSION 2.6)

project (Tutorial)
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/file_to_copy.py" DESTINATION "${CMAKE_BINARY_DIR}/")
add_executable(Tuto.out main.cpp)


