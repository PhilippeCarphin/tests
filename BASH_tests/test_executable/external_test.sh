#!/bin/bash

# This tests demonstrates the two test syntaxes in BASH.  The first one is
# actually using a program called '['.  This explains why spaces are needed
# everywhere.  The executable needs to get well separated command line
# arguments.  And there doesn't need to be a space between the ']' and ';'
# because ';' is a command terminator and doens't get inserted into the new
# process's argv[].

# The fact that [ is an external command makes it completely obvous why all
# these spaces are needed.  However, [[ ]] is a BASH builtin, so it might be
# able to handle a certain abscence of spaces but no, it behaves just like [ in
# that regard.  To to understand why [[ ]] needs spaces, I'll just use my
# understanding of why [ needs spaces and tell myself that [[ was made to behave
# the same way for consistency.

maximum=100000

stringa="Some say love, it is a river"
stringb="That drowns the tender reed"
################################################################################
# This test is done with the executable tester : /bin/[
################################################################################
function old_school(){
   if [ "$stringa" = "$stringb" ] ; then
      true
   else
      false
   fi
}

################################################################################
# This function uses the BASH built-in test
###############################################################################/
function new_school(){
   if [[ "$stringa" == "$scringb" ]]; then
      true
   else
      false
   fi
}

################################################################################
# First argument is a command, run it a bunch of times
################################################################################
function lots(){
   cmd=$1
   for ((i=0; $i<$maximum; ++i)) ; do
      $cmd
   done
}

time lots old_school
time lots new_school

exit 0
