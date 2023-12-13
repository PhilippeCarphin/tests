#!/bin/bash


echo "    ${BASH_SOURCE[0]}: \$\$ = $$"
echo "    ${BASH_SOURCE[0]}: BASHPID = ${BASHPID}"
echo "    ${BASH_SOURCE[0]}: MAIN_PID = ${MAIN_PID}"
echo "    ${BASH_SOURCE[0]}: PPID = ${PPID}"
echo -n "    ${BASH_SOURCE[0]}: pstree : "
pstree -p ${PPID}

if [[ $$ != ${BASHPID} ]] ; then
    echo "    ${BASH_SOURCE[0]}: I know I'm in a subshell!!!!!"
fi
