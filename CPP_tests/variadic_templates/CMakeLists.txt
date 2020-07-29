cmake_minimum_required(VERSION 3.10)

project(Variadic_Templates)
set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp)

if(${APPLE})
    find_package(TBB REQUIRED)
    set(TBB_LIBRARY TBB::tbb)
else()
    set(TBB_LIBRARY tbb)
endif()

target_link_libraries(main ${TBB_LIBRARY})

add_custom_target(check COMMAND ./main)
add_dependencies(check main)