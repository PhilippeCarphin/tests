#!/bin/bash

# Tests the following of a link I think this tests something in BASH that I
# wanted to use for my philconfig so that it could be called from anywhere.
# It used to be that you would need to call the install.sh script from the
# directory where it is, but I wanted it to be callable through a link as well.
#
# This is done using the readlink function.
#
# I remember reading about this on stack-overflow, there they suggested using a
# loop for reading links until we hit a non-link file
#
# Here I read the link only once and assume that there won't be more than one
# level of indirection.

echo '$0:'$0
echo $INSTALL_DIR

echo $(readlink $0)

if [ -L $0 ] ; then
   echo LINK
   LINK_TARGET=$(readlink $0)
   INSTALL_DIR=$(dirname $LINK_TARGET)
else
   echo REGULAR FILE
   INSTALL_DIR=$(dirname $PWD/$0)
fi

echo $INSTALL_DIR

if [ "$INSTALL_DIR" = /Users/pcarphin/Documents/GitHub/tests ] ; then
   echo TEST PASSED
else
   echo TEST FAILED
fi
