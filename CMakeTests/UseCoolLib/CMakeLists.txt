cmake_minimum_required(VERSION 3.16)

project(UseCoolLib VERSION 6.28.30 DESCRIPTION "Uses cool lib")

find_package(CoolLib REQUIRED COMPONENTS shades leatherjacket)
find_package(CoolLib REQUIRED COMPONENTS shared ompi)
find_package(CoolLib REQUIRED COMPONENTS)

add_executable(main main.c)
target_link_libraries(main PRIVATE CoolLib::leatherjacket CoolLib::shades)
