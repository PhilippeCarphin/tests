#!/bin/bash

# This test demonstrates a set of good options to set in scripts to detect
# a maximum amount of errors at the earliest moment

# Trigger exit and err trap in all almost all error circumstances (exceptions
# are when the command occurs in a command to create a list for a for loop:
# 'for x in $(ls noexist)'
set -e
set -o pipefail
set -E
shopt -s inherit_errexit
set -u
trap 'echo ${FUNCNAME[0]}:${LINENO}:${BASH_COMMAND}: ERRTRAP >&2 ; exit 9' ERR

function x(){
    # The `ls noexist` command triggers the trap but not the errexit.
    # Even if we put an `exit 9` in the trap, it only exits the subshell.
    for y in $(ls noexist) ; do
        echo "y=$y"
    done


    (echo "hello"; ((exit 8) | true); echo "goodbye")
    return 0
}

x
echo "end"
