#!/usr/bin/env bash

#
# Demonstration of the new BASH_TRAPSIG added in 5.3 which contains the
# signal number.
#
# Also something is weird about SIGCHLD.  I would have expected to get one
# SIGCHLD every time the sleep in the loop ends.  But instead we get more and
# more SIGCHLD's at each loop iteration.
#

# shopt -s checkwinsize
# (:)
declare -A bash_signames
printf "LINES:%s, COLUMNS:%S\n" "${LINES}" "${COLUMNS}"

bash_signames[0]=ERR
bash_signames[66]=ERR
bash_signames[65]=DEBUG
bash_signames[67]=RETURN
generic-trap-handler(){
    local signame=${bash_signames[${BASH_TRAPSIG}]:-$(builtin kill -l ${BASH_TRAPSIG})}
    case $signame in
        ERR|EXIT|TERM)
            printf "SIGNAL: ${signame}\n" ;;
        WINCH)
            printf "WindowSize: %dlines, %dcolumns\n" "${LINES}" "${COLUMNS}" ;;
        INT)
            printf "SIGNAL: INT -> exiting\n" ; exit ;;
    esac
}
term_received=0
trap 'printf "term\n" ; term_received=1' TERM
trap 'generic-trap-handler' ERR EXIT SIGINT SIGWINCH SIGPIPE RETURN SIGCHLD
trap 'generic-trap-handler' SIGUSR1 SIGUSR2 SIGPROF

f(){
    echo "f() returning"
}
false
f

trap -p return
printf "Grepping\n"
grep -r 'bingbong'
printf "Done grepping\n"

while !((term_received)); do
    printf "bingbong\n"
    sleep ${1:-10}
done
