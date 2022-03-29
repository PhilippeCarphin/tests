#!/bin/bash

if (return 0 >/dev/null 2>&1) ; then
    echo "Script is being SOURCED"
else
    echo "Script is being EXECUTED"
fi

# It is important to 'return 0' and not just do 'return'
# - If being executed, both 'return' and 'return 0' will fail but
# - If being sourced,  'return' would return the exit code of the last command
#   which could be non-zero.

if ! (return 0 >/dev/null 2>&1) ; then
    echo "ERROR: This script can only be sourced"
    exit 1
fi
