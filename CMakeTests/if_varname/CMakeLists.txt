cmake_minimum_required(VERSION 3.10)

set(MY_FILE "" CACHE FILEPATH "Path to some file")

if(MY_FILE)
    message(STATUS "MY_FILE is set : ${MY_FILE}")
else()
    message(STATUS "MY_FILE is empty")
endif()
