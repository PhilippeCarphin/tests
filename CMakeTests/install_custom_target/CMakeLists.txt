cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

add_custom_command(OUTPUT custom-file COMMAND touch custom-file COMMENT "Generating custom-file" DEPENDS input)
add_custom_target(custom ALL DEPENDS custom-file)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/custom-file DESTINATION share/${PROJECT_NAME}/)
