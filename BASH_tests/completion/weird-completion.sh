#!/usr/bin/env bash

# This completion will either
# - propose candidates that are ${cur}${l} for l in {a..z} or
# - propose only one candidate that is ${cur}${l} where l is the last letter of
#   ${cur}
# I think I just had the idea to do this and wanted to see how quickly I could
# do it.
#
_mycomp(){
    local cur=${COMP_WORDS[COMP_CWORD]}
    compopt -o nospace
    case ${cur: -1:1} in
        [a-m]|'')
            for a in {a..z} ; do
                COMPREPLY+=("${cur}$a")
            done
            ;;
        *)
            COMPREPLY+=("${cur}${cur: -1:1}")
            ;;
    esac
}
complete -F _mycomp c

