cmake_minimum_required(VERSION 3.10)

project(boost_permissions)
find_package(Boost COMPONENTS filesystem)

add_executable(main main.cpp)
# target_include_directories(main PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(main PRIVATE Boost::filesystem)