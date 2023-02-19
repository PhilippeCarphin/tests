
add_executable(climbingtool main.c)
target_link_libraries(climbingtool PRIVATE OpenSSL::SSL)

install(TARGETS climbingtool
    EXPORT ClimbingStatsTargets
    RUNTIME DESTINATION bin
)
