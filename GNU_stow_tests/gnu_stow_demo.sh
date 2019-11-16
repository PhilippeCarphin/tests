#!/bin/bash

is_relative_link(){
    [[ $1 != /* ]] && [ -L "$1" ]
}

follow_links()
{
    file="$(cd -P "$(dirname "$1")" > /dev/null && pwd)/$(basename "$1")"
    curr_dir="$(cd -P "$(dirname "$file")" > /dev/null && pwd)"
    while [ -L "$file" ] ; do
        curr_dir="$(cd -P "$(dirname "$file")" > /dev/null && pwd)"
        file="$(readlink "$file")"
        if is_relative_link "$file" ; then
            file="$curr_dir/$file"
        fi
    done
    echo "$file"
}

this_dir=$(dirname "$(follow_links "$0")")

link_dir=$this_dir/install-site
storage_dir=$this_dir/storage

cd $this_dir ; git clean -dfx

if [[ "$1" == --normal ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication --verbose 5
fi

if [[ "$1" == --ignore ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication --ignore 'an_application_other_subdir' --verbose 5
fi

if [[ "$1" == "--collision" ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$storage_dir" -S link_collision
fi

if [[ "$1" == "--override" ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$storage_dir" -S link_collision --override='.*'
fi

if [[ "$1" == "--file-collision" ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S file_collision --override='.*'
fi


