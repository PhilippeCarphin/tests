#!/bin/bash

inner(){
    echo "BASH_ARGC=(${BASH_ARGC[*]})"
    echo "BASH_ARGV=(${BASH_ARGV[*]})"
    echo "#FUNCNAME=${#FUNCNAME[@]}"
    echo "#BASH_ARGC=${#BASH_ARGC[@]}"
    if (( ${#FUNCNAME[@]} != ${#BASH_ARGC[@]} )) ; then
        echo "Script has 0 arguments"
    else
        echo "Script has arguments?"
    fi

    k=0
    for((i=0; i<${#FUNCNAME[@]}; i++)); do
        echo -n "FUNCNAME[$i] = ${FUNCNAME[i]}"
        for((j=${BASH_ARGC[i]-0}; j>0; j--)) ; do
            echo -n " '${BASH_ARGV[k+j-1]}'"
        done
        k=$((k+BASH_ARGC[i]))
        echo ""
    done
}

outer(){
    inner x y z
}

shopt -s extdebug
outer A B "C D E"
