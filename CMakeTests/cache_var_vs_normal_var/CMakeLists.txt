cmake_minimum_required(VERSION 3.16)

project(cache_vs_normal)

#
# This test demonstrates that you can have a non-cache variable and a cache
# variable with the same name.
#
# If there is just a CACHE variable, it can be accessed using ${}
# syntax as if it was a non-cache variable.  However, if there are both, then
# the ${} syntax will get the non-cache one and to get the cache variable
# we have to use $CACHE{}

set(MY_VAR "GOODBYE")
set(MY_VAR "HELLO" CACHE STRING "This is a cache variable")

message(STATUS "\${MY_VAR}=${MY_VAR}")
message(STATUS "\${CACHE{MY_VAR}=$CACHE{MY_VAR}")

set(MY_CACHE_VAR "GOOD MORNING" CACHE STRING "Another cache variable")

message(STATUS "\${MY_CACHE_VAR}=${MY_CACHE_VAR}")
message(STATUS "\${CACHE{MY_CACHE_VAR}=$CACHE{MY_CACHE_VAR}")
