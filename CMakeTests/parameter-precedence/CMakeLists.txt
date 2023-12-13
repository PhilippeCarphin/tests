cmake_minimum_required(VERSION 3.20)

project(test)

# This test demonstrates how to implement precedence
# 1 - Command line overrides
# 2 - Environment variable which overrides
# 3 - The default value

set(_init_with_my_thing TRUE)
if(DEFINED ENV{WITH_MY_THING})
    set(_init_with_my_thing $ENV{WITH_MY_THING})
endif()
set(WITH_MY_THING ${_init_with_my_thing} CACHE BOOL "Build with support for my-thing")

# If nothing is given, WITH_MY_THING's default value is 'in-code-default'
# and since no -DWITH_MY_THING was given on the command line, the value of
# WITH_MY_THING ends up being 'in-code-default'.
#
# If the environment variable is given, the default value of WITH_MY_THING is
# the value of that environment variable and since no -DWITH_MY_THING is given,
# the value of WITH_MY_THING ends up being the value of the environment variable
#
# If -DWITH_MY_THING is given, then that becomes the value of WITH_MY_THING
# regardless of the environment variable.
if(WITH_MY_THING)
    message("Yes, with my thing")
else()
    message("No, not with my thing")
endif()

# This is basically the same thing as above: Setting the default value of the
# cmake variable WITH_THAT_THING from the environment variable if it exists
# or a hardcoded default value otherwise.
if(DEFINED ENV{WITH_THAT_THING})
    set(WITH_THAT_THING $ENV{WITH_THAT_THING} CACHE BOOL "Build with support for that-thing")
else()
    set(WITH_THAT_THING TRUE CACHE BOOL "Build with support for that-thing")
endif()

if(WITH_THAT_THING)
    message("Yes, with that thing")
else()
    message("No, not with that thing")
endif()

#
# Another aproach would be
#
set(WITH_HELLO FALSE CACHE BOOL "help text")
if ((WITH_HELLO) OR (CACHE WITH_HELLO) OR ($ENV{WITH_HELLO}))
    message("HELLO!")
endif()
# But with that, if anyone of them is true, the expression is true so there is
# no precedence order so a user could do 'cmake .. -DWITH_HELLO=FALSE' but the
# environment variable, unbeknownst to them, is TRUE, then they will
#
# The OR approach with the if statements also has the disadvantage that a more
# complicated condition needs to be used everywhere that has code that is conditional on
# the value of WITH_HELLO whereas with my approach, the conditional code to get
# either the environment variable, the default value, or the command line value
# happens only once and the result of that logic is used later in the code.

