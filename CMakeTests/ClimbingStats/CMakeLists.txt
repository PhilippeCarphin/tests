cmake_minimum_required(VERSION 3.20)

project(ClimbingStats C Fortran)

set(PROJECT_VERSION 3.14.15)

find_package(LibXml2 REQUIRED)
find_package(OpenSSL REQUIRED)

add_subdirectory(src)

include(CMakePackageConfigHelpers)

set(CONFIG_INSTALL_DIR lib/cmake/climbingstats-${PROJECT_VERSION})
write_basic_package_version_file(
    climbingstats-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/climbingstats-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/climbingstats-version.cmake
    DESTINATION ${CONFIG_INSTALL_DIR})

install(EXPORT ClimbingStatsTargets
    FILE ClimbingStatsTargets.cmake
    DESTINATION ${CONFIG_INSTALL_DIR}
    NAMESPACE climbingstats::
    COMPONENT phil
)
