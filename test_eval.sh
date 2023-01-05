#!/bin/bash

# This test demonstrates that using 'eval' and a variable containing
# a command that itself contains '"$@"' keeps the correct word splitting
# even when '@' has some array elements that contain spaces.
#
# This is because the command that gets eval'd contains double quotes
# around the '$@'
#
function print_args(){
    for a in "$@"; do
        echo "arg = '$a'"
    done
}

function test_eval(){
    cmd='print_args "$@"'
    printf "echo \$cmd : \033[1;32m%s\033[0m\n" "$(echo $cmd)"
    printf "eval echo \$cmd : \033[1;32m%s\033[0m\n" "$(eval echo $cmd)"
    printf "eval \$cmd : ...\n"
    eval $cmd
    cmd_no_quotes='print_args $@'
    printf "echo \$cmd_no_quotes : \033[1;32m%s\033[0m\n" "$(echo $cmd_no_quotes)"
    printf "eval echo \$cmd_no_quotes : \033[1;32m%s\033[0m\n" "$(eval echo $cmd_no_quotes)"
    printf "eval \$cmd_no_quotes : ...\n"
    eval $cmd_no_quotes
}

test_eval A B C "D E F"

