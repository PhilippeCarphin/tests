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

cd $this_dir || exit &&  git clean -dfx install-site fresh_install_site

# This is the normal way, this will not run the operation if there
# are conflicts.  Note, the second stow has no conflicts.
if [[ "$1" == --normal ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
fi

# If stowing DIFFERENT files with the same name, then stow will
# not do the operation.  The first stow will succeed, the second
# will not.
if [[ "$1" == "--collision" ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$storage_dir" -S link_collision
fi

# If there are name conflicts, we can override.  This uses a regex as
# input so we can make it selective.
if [[ "$1" == "--override" ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$storage_dir" -S link_collision --override='.*'
fi

# If there are collisions with files, then even override won't get
# stow to help you there.  It's better that way.
if [[ "$1" == "--file-collision" ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S file_collision --override='.*'
fi

# We can ignore subdirectories of our packages
if [[ "$1" == --ignore ]] ; then
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication --ignore 'an_application_other_subdir' --verbose 5
fi

new_link_dir=$this_dir/fresh_install_site

# Demo with fresh directory, Things to note: After the first stow,
# $new_link_dir/bin will be a link pointing to ../storage/AnApplication/bin but
# after the second stow, since both packages have subdirectories called bin,
# stow will replace the link to ../storage/AnApplication/bin with a directory
# containing links to all the files in ../storage/AnApplication/bin and then
# will do the links for OtherApplication.
if [[ $1 == --fresh ]] ; then
    stow -t "$new_link_dir" -d "$storage_dir" -S AnApplication
    echo "== First one =="
    tree -l $new_link_dir
    echo "== Second one ="
    stow -t "$new_link_dir" -d "$storage_dir" -S OtherApplication
    tree -l $new_link_dir
fi

other_storage_dir=$this_dir/other-storage

if [[ $1 == -different-storage ]] ; then
    stow -t "$new_link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$new_link_dir" -d "$other_storage_dir" -S OtherApplication
