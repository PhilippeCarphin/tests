#!/bin/bash

set +x

echo "Before subshell : $(shopt -o errexit)"
(
    set -e
    printf "Inside subshell   "
    shopt -o errexit
    false
    echo "subshell after false"
)


echo "After subshell : $(shopt -o errexit)"
