cmake_minimum_required(VERSION 3.20)

project(unix_sockets C)

add_executable(server main.c)
add_executable(client client.c)
