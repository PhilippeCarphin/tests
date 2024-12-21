cmake_minimum_required(VERSION 3.20)

project(X C Fortran)

#
# This test demonstrates that if(DEFINED ...) for argumetns only works with
# functions
#

function(func_argv0)
    message(STATUS "(EC) func_argv0 ARGV0=${ARGV0}")
    if(DEFINED ARGV0)
        message(STATUS "(EC) func_argv0 ARGV0 is defined")
        set(MANIFEST_FILE ${ARGV0}/MANIFEST PARENT_SCOPE)
    else()
        message(STATUS "(EC) func_argv0 ARGV0 is NOT defined")
        set(MANIFEST_FILE MANIFEST PARENT_SCOPE)
    endif()
endfunction()

macro(macro_argv0)
    message(STATUS "(EC) macro_argv0: ARGV0=${ARGV0}")
    if(DEFINED ARGV0)
        message(STATUS "(EC) macro_argv0: ARGV0 is defined")
        set(MANIFEST_FILE ${ARGV0}/MANIFEST)
    else()
        message(STATUS "(EC) macro_argv0: ARGV0 is NOT defined")
        set(MANIFEST_FILE MANIFEST)
    endif()
endmacro()

message(STATUS "MAIN: function with an arg:...")
func_argv0(longitude)
message(STATUS "MAIN: MANIFEST_FILE=${MANIFEST_FILE}")
unset(MANIFEST_FILE)
message("")

message(STATUS "MAIN: function with NO arg:...")
func_argv0()
message(STATUS "MAIN: MANIFEST_FILE=${MANIFEST_FILE}")
unset(MANIFEST_FILE)
message("")

message(STATUS "MAIN: macro with an arg:...")
macro_argv0(lattitude)
message(STATUS "MAIN: MANIFEST_FILE=${MANIFEST_FILE}")
unset(MANIFEST_FILE)
message("")

message(STATUS "MAIN: macro with NO arg:...")
macro_argv0()
message(STATUS "MAIN: MANIFEST_FILE=${MANIFEST_FILE}")
unset(MANIFEST_FILE)
message("")

