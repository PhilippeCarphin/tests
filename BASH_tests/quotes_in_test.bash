#!/bin/bash

a=" x "
b=" x"
c=" "

#
# An extra test: someone pointed out that variables don't need to be quoted in
# [[ ... ]] and I was sure that they needed quotes when the variable could be
# empty or have spaces.  Now I'm pretty sure that the cases where they were
# needed were because I was using [ ... ].
#
# Even with spaces in the valeues of the variables, we get the correct results
# with [[ ... ]]
#

if [[ $a == $b ]] ; then
    echo "[[ ... ]] YES"
else
    echo "[[ ... ]] NO"
fi

if [ $a == $b ] ; then
    echo "[ ... ] YES"
else
    echo "[ ... ] NO"
fi

if [ $c == $b ] ; then
    echo "[ ... ] YES"
else
    # If something prevents [ from working properly, we go here because
    # [ it will return a non-zero exit code
    echo "[ ... ] NO"
fi
