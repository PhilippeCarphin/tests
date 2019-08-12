#!/bin/bash

# Change this to false to see why the 'if is_relative_link' part is necessary.
handle_relative_links=true

is_relative_path(){
    [[ $1 != /* ]]
}

# Portable normalization for OSX
portable_normpath(){
    echo "$(cd -P "$(dirname $1)" > /dev/null && pwd)/$(basename $1)"
}

shell_follow_links()
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

py_follow_links()
{
    python -c "import os,sys; print(os.path.realpath(sys.argv[1]))" $1
}

follow_links(){
    shell_follow_links $@
}

other_follow_links(){
    target=$1

    cd $(dirname $target)
    target=$(basename $target)

    while [ -L $target ] ;
    do
          target=$(readlink $target)
          cd $(dirname $target)
          target=$(basename $target)
    done

    dir=$(pwd -P)
    file=$dir/$target

    echo $file
}
