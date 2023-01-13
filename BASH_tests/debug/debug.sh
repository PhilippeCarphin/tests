#!/bin/bash

set -x
#
# This is the best way I've found to debug BASH scripts and collections
# of bash scripts that use sourcing.  It is self explanatory but the output
# from doing `set -x` will contain the file and line number of the line
# being executed.
#
# If the BASH script we are debugging *runs* other bash scripts, then
# exporting this variable would affect those scripts as well, unfortunately
# if those scripts don't turn on `set -x` we won't see any debug output
# from them.  If they do turn it on and don't set PS4, then exporting this
# PS4 will affect them.
#
PS4='+ [${BASH_SOURCE[0]}:${LINENO}]'

#
# It is common to use `echo` or `printf` to display information to the user
# and it can be annoying to have the such commands displayed in the debug
# output.
#
# A technique that can be used is the following:
#
{ printf "\033[1;32mThis is some info for the user\033[0m\n" ; } 2>/dev/null

#
# It has to be the output STDERR of the block that CONTAINS the command that
# is redirected to /dev/null:
#
printf "\033[1;33mThis is more info, but the printf shows in debug output\033[0m\n" 2>/dev/null

#
# I think this should only be used if we are writing a script that is meant to
# have `set -x` turned on since the fact that we put `set -x` at the top of the
# script makes it so that fewer prints are needed and therefore the tedium of
# putting them all inside { ... ; } 2>/dev/null is not so bad.
#
# I wanted to find a way to override echo or printf so that all echo commands
# would be exclude from `set -x` output but I couldn't find a satisfactory
# solution.  And really it's not that bad to have the prints in the debug
# output.  It's just nice to know this technique.
#
