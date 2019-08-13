cmake_minimum_required(VERSION 2.8)
project(boost_logging)

set(CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE(main main.cpp)

# Adding the system component is necessary for the
# #include <boost/log/expression.hpp>.
# When I start including that file, I got linker errors for
# symbols of the system component of boost.
# Added the 'system' component
FIND_PACKAGE(Boost COMPONENTS log system REQUIRED)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
TARGET_INCLUDE_DIRECTORIES(main PRIVATE ${Boost_INCLUDE_DIR})
# Added linking to the 'system' library of boost
TARGET_LINK_LIBRARIES(main ${Boost_LIBRARIES})

FIND_PACKAGE(Threads)
TARGET_LINK_LIBRARIES(main ${CMAKE_THREAD_LIBS_INIT})
