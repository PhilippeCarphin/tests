cmake_minimum_required(VERSION 3.16)
project(math)
#
# This test demonstrates using the use of `math(EXPR` and
# also confirms that it does not output to CACHE variables
#
# To set a cache variable with the result of some calculations
# doesn't really make sense anyway.
#
set(result "0" CACHE STRING "Math")

math(EXPR result "${no_exist} + 1")
message(STATUS "result=${result}")

math(EXPR result "${result} + 1")
message(STATUS "result=${result}")

message(STATUS "\$CACHE{result}=$CACHE{result}")
