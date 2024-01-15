cmake_minimum_required(VERSION 3.16)

project(test)

#
# This test demonstrates that when a variable like CMAKE_PREFIX_PATH is both
# a CMake variable and an environment variable, the environment variable is
# not used to initialize the CMake variable, instead, CMake just looks at both
# variables when searching for packages.
#
# The documentation doesn't say so explicitly but it is worded in such a way
# that it leads one is most likely to come to the correct conclusion that the
# two variables are separate and CMake just looks at both of them.
#
# As for the order as, placing two copies of a package putting the location of
# one copy in the CMake variable and the location of the other in the environment
# variable, we can see that the CMake variable is searched first.
#
# However in this instance, if <X>/bin is in the environment variable PATH, then
# the one in <X> will be found first.
# set(CMAKE_PREFIX_PATH /home/phc001/Repositories/gitlab.science.gc.ca/RPN-SI/librmn/localinstall)

message(CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH})
message(ENV:CMAKE_PREFIX_PATH=$ENV{CMAKE_PREFIX_PATH})


find_package(rmn REQUIRED)
