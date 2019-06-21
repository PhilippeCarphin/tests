cmake_minimum_required(VERSION 3.10)
project(boost_logging)
set(CMAKE_CXX_STANDARD 14)


# SET(Boost_USE_STATIC_LIBS ON)
# FIND_PACKAGE(Boost COMPONENTS log REQUIRED)
# # find_package(Boost COMPONENTS log)
# add_executable(boost_logging main.cpp)
# target_link_libraries(boost_logging ${Boost_LOG_LIBRARIES})

# CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE(Boost COMPONENTS log REQUIRED)
FIND_PACKAGE(Threads)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main ${Boost_LOG_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})