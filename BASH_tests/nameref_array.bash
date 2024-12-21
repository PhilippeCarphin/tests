#!/bin/bash

#
# This test demonstrates that we can use namerefs for arrays.  Just to check
# because someone said someone said something that seemed contrary to that but
# it's just that a variable cannot be both an array and a nameref.  We can
# still use a nameref to refer to an array.

main(){
    local arr=("a b c" "x y z")
    if array_contains arr "a b c" ; then
        echo "YES array arr does contain 'a b c'"
    else
        echo "NO"
    fi
}

array_contains(){
    local -n array=${1}
    if [[ ${array@a} != *a* ]] ; then
        echo "${FUNCNAME[0]}: ERROR: First argument must be the name of an array variable"
    fi
    local x
    for x in "${array[@]}" ; do
        echo "x='${x}'"
        if [[ "${x}" == "${2}" ]] ; then
            return 0
        fi
    done
    return 1;
}

main

var=value
varname=var

arr=(1 2 3 "4 5 6")
arrname=arr

declare -A map
map[x]=y
map[u]=v
echo ${!map[@]}

# Value of variable whose name is ${varname}
echo ${!varname}

# Keys of array
echo ${!arr[@]}
