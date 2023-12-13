cmake_minimum_required(VERSION 3.16)

project(test_install_local C Fortran)

# I'm testing to what gets installed so I don't want to be confused by things
# that were in the install dir from previous installs
add_custom_target(t COMMAND rm -rf ${CMAKE_INSTALL_PREFIX} COMMENT "Deleting install dir")

add_executable(toplevel toplevel.c)

add_subdirectory(subdir)

# install(CODE "execute_process(COMMAND mkdir -p ${CMAKE_INSTALL_PREFIX} COMMAND ln -sf ${CMAKE_SOURCE_DIR}/CMakeLists.txt ${CMAKE_INSTALL_PREFIX})")
install(CODE "execute_process(COMMAND touch ${CMAKE_INSTALL_PREFIX}/file)")
# add_custom_target(config_link COMMAND ln -sf ${CMAKE_SOURCE_DIR}/CMakeLists.txt ${CMAKE_BINARY_DIR}/ OUTPUT ${CMAKE_BINARY_DIR}/CMakeLists.txt)


install(TARGETS toplevel)

############################### ORIGINAL FROM GEM ##############################
# add_custom_target(work
#     COMMAND /bin/mkdir -p ${WORK_PREFIX}
#     COMMAND /bin/mkdir -p ${WORK_PREFIX}/bin
#     COMMAND /bin/ln -sf ${CMAKE_SOURCE_DIR}/share/configurations ${WORK_PREFIX}
#     COMMAND cd ${CMAKE_BINARY_DIR} && make install/local
#   )
#
# NOTE: This way, doing 'make install' does not create the link
#
############################### BETTER SOLUTION ################################
# install(CODE "execute_process(COMMAND ln -sf ${CMAKE_SOURCE_DIR}/share/configurations ${WORK_PREFIX})")
# add_custom_target(work
#     COMMAND /bin/mkdir -p ${WORK_PREFIX}
#     COMMAND /bin/mkdir -p ${WORK_PREFIX}/bin
#     COMMAND cd ${CMAKE_BINARY_DIR} && make install/local
#   )
#
# NOTE: Now 'make install/local', 'make work', and 'make install' will all
# create the link because the task of creating the link has been specified
# as something to do when installing instead of something to do ONLY when
# 'make work' is called.
################################################################################
