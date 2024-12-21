cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

install(CODE "message(\"Code that runs at install (and package) time\")
execute_process(COMMAND date OUTPUT_VARIABLE PACKAGE_TIMESTAMP)
configure_file(${CMAKE_SOURCE_DIR}/configure_file.in ${CMAKE_BINARY_DIR}/configure_file.out @ONLY)
# execute_process(COMMAND touch ${CMAKE_INSTALL_PREFIX}/FILE_BAD) [1]
execute_process(COMMAND touch \${CMAKE_INSTALL_PREFIX}/FILE_GOOD)")

install(FILES ${CMAKE_BINARY_DIR}/configure_file.out DESTINATION .ssm.d)

set(CPACK_GENERATOR "TGZ")
include(CPack)


# [1] This doesn't work.  As I understand it, the package generator runs a
# something like a make install with a different CMAKE_INSTALL_PREFIX.  We need
# to delay the resolution of CMAKE_INSTALL_PREFIX until the moment the package
# generator runs.  That line, if uncommented, results in permission denied
# if we have not set CMAKE_INSTALL_PREFIX.  If we have set it, then when we
# run `make package, the file will be created in the CMAKE_INSTALL_PREFIX that
# was given *when the user ran CMake* not the temporary one set by the package
# generator (the package won't contain the file).
