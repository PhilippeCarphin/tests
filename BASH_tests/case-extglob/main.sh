#!/bin/bash

# This test demonstrates some of the things that can be done when extglob
# shell option is activated

shopt -s extglob
do-case(){

    for x in xyya abyy "caaa baab" axyy Axx AxxB ; do
        case $x in
            @(A*|*B)) echo "$x starts with A or ends with B" ;;
            ?(*a*|*b*)) echo "$x contains at least one 'a'" ;&
            !(a*|b*|c*)) echo "$x does not start with a, b, or c" ;;
            *) echo "$x did not match anything" ;;
        esac
    done
}

do-case "$@"
