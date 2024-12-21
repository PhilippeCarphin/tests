cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

# This demonstrates that trying to do a regex match on an empty string is
# an error in CMake which is absolutely crazy!
#
# Can't it just return an empty result?

set(empty_string "")
string(REGEX MATCH "[a-z]*" result "${empty_string}")
message(STATUS "result='${result}'")
