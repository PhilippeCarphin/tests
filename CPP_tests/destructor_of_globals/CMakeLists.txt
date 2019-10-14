PROJECT(dest_test CXX)
set(CMAKE_CXX_STANDARD 17)

# add_library(phil-logger SHARED PhilLogger.cpp)
# add_library(other-lib SHARED OtherClass.cpp)
# target_link_libraries(other-lib PRIVATE phil-logger)
add_executable(main main.cpp PhilLogger.cpp OtherClass.cpp)
# target_link_libraries(main PRIVATE phil-logger other-lib)