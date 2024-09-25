cmake_minimum_required(VERSION 3.16)
project(default_install_prefix C)

#
# This test demonstrates the variable CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
# and how this is different from detecting that the install prefix is equal to
# /usr/local.  See run.sh
#

if(CMAKE_INSTALL_PREFIX STREQUAL /usr/local)
    message(STATUS "CMAKE_INSTALL_PREFIX is /usr/local")
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(STATUS "CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT: TRUE")
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install-dir CACHE PATH "..." FORCE)
    message(STATUS "Set CMAKE_INSTALL_PREFIX to ${CMAKE_INSTALL_PREFIX}")
else()
    message(STATUS "CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT: FALSE")
endif()

install(FILES CMakeLists.txt DESTINATION x)

