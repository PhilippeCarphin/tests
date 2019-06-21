cmake_minimum_required(VERSION 3.10)
project(boost_logging)

set(CMAKE_CXX_STANDARD 14)

ADD_EXECUTABLE(main main.cpp)

# Adding the system component is necessary for the
# #include <boost/log/expression.hpp>.
# When I start including that file, I got linker errors for
# symbols of the system component of boost.
# Added the 'system' component
FIND_PACKAGE(Boost COMPONENTS log system thread REQUIRED)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
TARGET_INCLUDE_DIRECTORIES(main PRIVATE ${Boost_INCLUDE_DIR})
# This line on it's own would work but to know which component was
# causing the linking error, ...
# TARGET_LINK_LIBRARIES(main ${Boost_LIBRARIES})

# I included libraries one by one until I found out that it
# was the Boost_THREAD_LIBRARY that needed to be linked with
# (I was already linking with Boost_SYSTEM_LIBRARY)
TARGET_LINK_LIBRARIES(main ${Boost_LOG_LIBRARY})
# TARGET_LINK_LIBRARIES(main ${Boost_DATE_TIME_LIBRARY})
# TARGET_LINK_LIBRARIES(main ${Boost_LOG_SETUP_LIBRARY})
TARGET_LINK_LIBRARIES(main ${Boost_SYSTEM_LIBRARY})
# TARGET_LINK_LIBRARIES(main ${Boost_FILESYSTEM_LIBRARY})
TARGET_LINK_LIBRARIES(main ${Boost_THREAD_LIBRARY})
# TARGET_LINK_LIBRARIES(main ${Boost_REGEX})
# TARGET_LINK_LIBRARIES(main ${Boost_CHRONO})
# TARGET_LINK_LIBRARIES(main ${Boost_ATOMIC})

FIND_PACKAGE(Threads)
TARGET_LINK_LIBRARIES(main ${CMAKE_THREAD_LIBS_INIT})
