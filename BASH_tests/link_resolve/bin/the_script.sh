#!/bin/bash

is_relative_path(){
    [[ $1 != /* ]]
}

# Portable normalization for OSX
portable_normpath(){
    echo "$(cd -P "$(dirname $1)" > /dev/null && pwd)/$(basename $1)"
}

follow_links()
{
    local file="$(portable_normpath $1)"
    local curr_dir="$(dirname $file)"
    while [ -L $file ] ; do
        curr_dir="$(dirname $file)"
        file="$(readlink $file)"
        if is_relative_path $file ; then
            file="$curr_dir/$file"
        fi
    done
    file=$(portable_normpath $file)
    echo $file
}

