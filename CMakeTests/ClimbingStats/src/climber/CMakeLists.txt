
add_library(climber SHARED climber.c)
target_link_libraries(climber PUBLIC LibXml2::LibXml2)
set_target_properties(climber PROPERTIES
    PUBLIC_HEADER climber.h
    INTERFACE_INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_compile_options(climber PRIVATE -Wall)
target_compile_definitions(climber PUBLIC CLIMBER_VERSION=1)

install(
    TARGETS climber
    EXPORT ClimbingStatsTargets
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    INCLUDES DESTINATION include)

