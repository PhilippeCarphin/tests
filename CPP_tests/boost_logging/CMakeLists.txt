cmake_minimum_required(VERSION 3.10)
project(boost_logging)

# Side note: This allows IDEs like CLion to know which standard you
# are using.
set(CMAKE_CXX_STANDARD 14)

# Modern CMake versions should come with a module for this.
FIND_PACKAGE(Boost COMPONENTS log REQUIRED)

# This one is required because of some weirdness with dynamic
# linking and boost.
# FROM THE DOC : https://www.boost.org/doc/libs/1_54_0/libs/log/doc/html/log/rationale/namespace_mangling.html
# Namespace mangling may lead to linking errors if the application is
# misconfigured. One common mistake is to build dynamic version of the library and
# not define BOOST_LOG_DYN_LINK or BOOST_ALL_DYN_LINK when building the
# application, so that the library assumes static linking by default. Whenever
# such linking errors appear, one can decode the namespace name in the missing
# symbols and the exported symbols of Boost.Log library and adjust library or
# application configuration accordingly.
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)


ADD_EXECUTABLE(main main.cpp)

# At CMC, this line is not necessary, probably because on my mac
# libraries are installed in places that g++ doens't look in automatically.
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# Not Boost_LOG_LIBRARY, not BOOST_LOG_LIBRARIES, not boost_LOG_LIBRARIES,
# it's Boost_LOG_LIBRARIES
TARGET_LINK_LIBRARIES(main ${Boost_LOG_LIBRARIES})
