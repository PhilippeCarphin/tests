cmake_minimum_required(VERSION 3.20)


project(unix_sockets C)

find_package(Threads REQUIRED)

add_executable(server main.c)
target_link_libraries(server PRIVATE Threads::Threads)
add_executable(client client.c)
