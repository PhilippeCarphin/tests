cmake_minimum_required(VERSION 3.20)

function(truthiness YAYBOO)
    if(YAYBOO)
        message(STATUS "The [34mdirect[0m value '${YAYBOO}' \tis [32mtruthy[0m")
    else()
        message(STATUS "The [34mdirect[0m value '${YAYBOO}' \tis [31mfalsy[0m")
    endif()
endfunction()

function(truthiness_deref YAYBOO)
    if(${YAYBOO})
        message(STATUS "The [36mderef[0m value '${YAYBOO}' \tis [32mtruthy[0m")
    else()
        message(STATUS "The [36mderef[0m value '${YAYBOO}' \tis [31mfalsy[0m")
    endif()
endfunction()
message(STATUS "---- Generic values ----")
truthiness(yayboo)
truthiness_deref(yayboo)
truthiness(f)
truthiness_deref(f)
truthiness(t)
truthiness_deref(t)

message(STATUS "---- Boolean style values ----")
truthiness(YES)
truthiness_deref(YES)

truthiness(ON)
truthiness_deref(ON)

truthiness(1)
truthiness_deref(1)

truthiness(0)
truthiness_deref(0)

truthiness(y)
truthiness_deref(y)

truthiness(n)
truthiness_deref(n)

truthiness(yayboo-NOTFOUND)
truthiness_deref(yayboo-NOTFOUND)

message(STATUS "-------------")

truthiness(YES)
truthiness(TRUE)
truthiness(True)
truthiness(On)
truthiness(ON)
truthiness(1)
truthiness(0)
truthiness(false)
truthiness(yayboo-NOTFOUND)
message(STATUS "-------------")

truthiness_deref(YES)
truthiness_deref(TRUE)
truthiness_deref(True)
truthiness_deref(On)
truthiness_deref(ON)
truthiness_deref(1)
truthiness_deref(0)
truthiness_deref(false)
truthiness_deref(yayboo-NOTFOUND)

message(STATUS "-------------")

truthiness(yayboo)
truthiness_deref(yayboo)

truthiness(f)
truthiness_deref(f)

