cmake_minimum_required(VERSION 3.10)

project(python_cxx_module C)

# Youcompleteme
# https://bastian.rieck.me/blog/posts/2015/ycm_cmake/
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )
IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()


if(NOT APPLE)
    find_package(PythonLibs 3 REQUIRED)
    python_add_module(integration_csin_straight_c integration_csin_straight_c.c)
else()
    # set(PYTHON_LIBRARY /opt/homebrew/Cellar/python@3.9/3.9.5/Frameworks/Python.framework/Versions/3.9/lib/libpython3.9.dylib)
    # set(PYTHON_LIBRARY_DIR /opt/homebrew/Cellar/python@3.9/3.9.5/Frameworks/Python.framework/Versions/3.9/include)
    find_package(Python 3 REQUIRED Development)
    Python_add_library(integration_csin_straight_c MODULE integration_csin_straight_c.c)
endif()


target_link_libraries(integration_csin_straight_c PRIVATE ${PYTHON_LIBRARIES})
target_include_directories(integration_csin_straight_c PRIVATE ${PYTHON_INCLUDE_DIRS})
