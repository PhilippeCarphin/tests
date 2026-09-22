#!/usr/bin/env bash
shopt -s expand_aliases

# In his video, Dave Eddy shows a cool trick to improve performance when not
# debugging.
#
#    https://youtu.be/1ybscUtrxzA?si=3DbmOfzUCPArl3mQ&t=556
#
# Aliasing debug to '#' instead of 'debug-func' speeds up execution when DEBUG
# is off but at the cost of some risks.

if [[ -n $DEBUG ]] ; then
    alias debug=debug-func
else
    alias debug=#
fi

debug-func(){
    printf "DEBUG: %s\n" "$*" >&2
}

main(){
    echo hello

    debug "start of main"

    # RISK: Creating an empty if statement
    # This causes "syntax error near unexpected token `fi'"
    if ((x == y)) ; then
        debug "foo"
    fi

    # RISK: Not interpreting a '\' that extends a line
    # this causes "Second arg: command not found"
    debug "First arg" \
        "Second arg"

    echo world
}
main "$@"
