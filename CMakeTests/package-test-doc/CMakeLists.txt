cmake_minimum_required(VERSION 3.21)

project(Climbing C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(Climging_VERSION 3.4.1)

include(GenerateExportHeader)

add_library(ClimbingStats SHARED climbingstats.c)
generate_export_header(ClimbingStats)
set_property(TARGET ClimbingStats PROPERTY VERSION ${Climging_VERSION})
set_property(TARGET ClimbingStats PROPERTY SOVERSION 3)
set_property(TARGET ClimbingStats PROPERTY INTERFACE_ClimbingStats_MAJOR_VERSION 3)
set_property(TARGET ClimbingStats APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ClimbingStats_MAJOR_VERSION)

install(TARGETS ClimbingStats EXPORT ClimbingStatsTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)
install(
  FILES
    climbingstats.h
    "${CMAKE_CURRENT_BINARY_DIR}/climbingstats_export.h"
  DESTINATION
    include
  COMPONENT
    Devel
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/ClimbingStats/ClimbingStatsConfigVersion.cmake"
  VERSION ${Climging_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT ClimbingStatsTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/ClimbingStats/ClimbingStatsTargets.cmake"
  NAMESPACE ClimbingNS::
)
configure_file(cmake/ClimbingStatsConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/ClimbingStats/ClimbingStatsConfig.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/cmake/ClimbingStats)
install(EXPORT ClimbingStatsTargets
  FILE
    ClimbingStatsTargets.cmake
  NAMESPACE
    ClimbingINS::
  DESTINATION
    ${ConfigPackageLocation}
)

install(
  FILES
    cmake/ClimbingStatsConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/ClimbingStats/ClimbingStatsConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)
