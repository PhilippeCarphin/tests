cmake_minimum_required(VERSION 3.16)

project(parse_args C Fortran)

# See `syntax/cmake.vim` in my vim config repo and search for `my_macro` to see
# how the keywords can be added to the syntax so that they are highlighted only
# within `my_func`.

function(my_func)
    cmake_parse_arguments(PARSE_ARGV 0 MY_FUNC "FLAG1;FLAG2" "BOSS;DIRECTOR" "EMPLOYEES;INTERNS")
    message(STATUS "*** my_func ***")
    message(STATUS "ARGN=${ARGN}")
    message(STATUS "ARGV=${ARGV}")
    message(STATUS "MY_FUNC_FLAG1=${MY_FUNC_FLAG1}")
    message(STATUS "MY_FUNC_FLAG2=${MY_FUNC_FLAG2}")
    message(STATUS "MY_FUNC_BOSS=${MY_FUNC_BOSS}")
    message(STATUS "MY_FUNC_DIRECTOR=${MY_FUNC_DIRECTOR}")
    message(STATUS "MY_FUNC_EMPLOYEES=${MY_FUNC_EMPLOYEES}")
    message(STATUS "MY_FUNC_INTERNS=${MY_FUNC_INTERNS}")
    message(STATUS " MY_FUNC_UNPARSED_ARGUMENTS=${MY_FUNC_UNPARSED_ARGUMENTS}")
    if(MY_FUNC_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Function '${CMAKE_CURRENT_FUNCTION}' incorrect arguments '${MY_FUNC_UNPARSED_ARGUMENTS}' are unparsed")
    endif()
endfunction()

my_func(
    BOSS "JP"
    DIRECTOR "JF"
    EMPLOYEES "John" "Robert" "Dana" "Fox"
    INTERNS "Bobby" "Timmy"
    FLAG2
)

macro(my_macro)
    cmake_parse_arguments(MY_MACRO "FLAG1;FLAG2" "BOSS;DIRECTOR" "EMPLOYEES;INTERNS" "${ARGN}")
    message(STATUS "*** my_macro ***")
    message(STATUS "MY_MACRO_FLAG1=${MY_MACRO_FLAG1}")
    message(STATUS "MY_MACRO_FLAG2=${MY_MACRO_FLAG2}")
    message(STATUS "MY_MACRO_BOSS=${MY_MACRO_BOSS}")
    message(STATUS "MY_MACRO_DIRECTOR=${MY_MACRO_DIRECTOR}")
    message(STATUS "MY_MACRO_EMPLOYEES=${MY_MACRO_EMPLOYEES}")
    message(STATUS "MY_MACRO_INTERNS=${MY_MACRO_INTERNS}")
    message(STATUS " MY_MACRO_UNPARSED_ARGUMENTS=${MY_MACRO_UNPARSED_ARGUMENTS}")
    if(MY_MACRO_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Macro called with incorrect arguments '${MY_MACRO_UNPARSED_ARGUMENTS}' are unparsed")
    endif()
endmacro()

my_macro(
    FLAG2
    BOSS "JP"
    DIRECTOR "JF"
    EMPLOYEES "John" "Robert" "Dana" "Fox"
    INTERNS "Bobby" "Timmy"
)

