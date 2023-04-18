cmake_minimum_required(VERSION 3.16)

project(CoolLib LANGUAGES C VERSION 3.14.15)

include(GNUInstallDirs) # For CMAKE_INSTALL_LIBDIR and CMAKE_INSTALL_INCLUDEDIR
                        # which just expand to 'lib' and 'include' respectively

set(CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION})

add_subdirectory(src)

install(FILES config.cmake
    RENAME ${PROJECT_NAME}Config.cmake
    DESTINATION ${CONFIG_INSTALL_DIR})
