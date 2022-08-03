#!/bin/bash

#
# This test demonstrates that the method of distinguishing sourcing and execution
# using 'if (return 0) ; then ...' can only be used outside a function and
# thus is an acceptable exception to my best practice of never putting any
# naked code in a bash script except the call to main
#
function main(){
    if (return 0) ; then
        echo "This file is being SOURCED"
    else
        echo "This file is being EXECUTED"
    fi
    echo "inside main"
}

main
