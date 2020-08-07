cmake_minimum_required(VERSION 3.10)

project(bpo_no_macros CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS program_options)

add_executable(main bpo_no_macros.cpp)

target_link_libraries(main PRIVATE Boost::program_options)
target_include_directories(main PRIVATE ${Boost_INCLUDE_DIRS})
message(STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")