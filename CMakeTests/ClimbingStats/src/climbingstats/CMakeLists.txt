
add_library(climbingstats SHARED climbingstats.c climbingstats.F90)
target_link_libraries(climbingstats PUBLIC climber)
set_target_properties(climbingstats PROPERTIES
    PUBLIC_HEADER climbingstats.h
    INTERFACE_INCLUDE_DIRECTORIES $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_compile_options(climbingstats PRIVATE $<$<COMPILE_LANGUAGE:C>:-Werror=implicit-function-declaration>)
target_compile_definitions(climbingstats
    PUBLIC
        $<$<COMPILE_LANGUAGE:C>:SOME_C_DEFINE=1>
        $<$<COMPILE_LANGUAGE:Fortran>:SOME_FORTRAN_DEFINE=2>
)

install(
    TARGETS climbingstats
    EXPORT ClimbingStatsTargets
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    INCLUDES DESTINATION include)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/climbingstats.mod
    TYPE INCLUDE)
