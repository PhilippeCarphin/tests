cmake_minimum_required(VERSION 3.20)

project(foreach_demo C Fortran)

set(database_files
    db1.sqlite
    db2.sqlite
    db3.sqlite
)
include(CTest)
function(do_thing name)
    add_executable(${name} main.c)
    message(STATUS "do_thing: name=${name}")
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}> a b "C D")
endfunction()

do_thing(the_fonz)

target_link_libraries(the_fonz PRIVATE m)

foreach(db IN LISTS database_files)
    message(STATUS "db = ${db}")
endforeach()

foreach(db IN ITEMS ${database_files})
    message(STATUS "db = ${db}")
endforeach()
