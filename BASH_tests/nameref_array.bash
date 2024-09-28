#!/bin/bash


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

echo ${!varname}
echo ${!arr[@]}


a=" x "
b=" x"

if [[ $a == $b ]] ; then
    echo "YES"
else
    echo "NO"
fi
