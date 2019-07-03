#!/bin/bash

# Change this to false to see why the 'if is_relative_link' part is necessary.
handle_relative_links=true

is_relative_link(){
    [[ $1 != /* ]]
}

portnorm(){
    echo "$(cd -P "$(dirname $1)" > /dev/null && pwd)/$(basename $1)"
}

follow_links()
{
    local file="$(portnorm $1)"
    local curr_dir="$(cd -P "$(dirname $file)" > /dev/null && pwd)"
    while [ -L $file ] ; do
        curr_dir="$(cd -P "$(dirname $file)" > /dev/null && pwd)"
        file="$(readlink $file)"
        if is_relative_link $file ; then
            file="$curr_dir/$file"
        fi
    done
    file=$(portnorm $file)
    echo $file
}

