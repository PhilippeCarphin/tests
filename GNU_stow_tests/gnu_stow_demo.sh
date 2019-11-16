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
new_link_dir=$this_dir/fresh_install_site
other_storage_dir=$this_dir/other-storage

cd $this_dir || exit &&  git clean -dfx install-site fresh_install_site

case $1 in
# This is the normal way, this will not run the operation if there
# are conflicts.  Note, the second stow has no conflicts.
--normal)
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    ;;
# If stowing DIFFERENT files with the same name, then stow will
# not do the operation.  The first stow will succeed, the second
# will not.
--collision)
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$storage_dir" -S link_collision
    ;;

# If there are name conflicts, we can override.  This uses a regex as
# input so we can make it selective.
--override)
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$storage_dir" -S link_collision --override='.*'
    ;;

# If there are collisions with files, then even override won't get
# stow to help you there.  It's better that way.
--file-collision)
    stow -t "$link_dir" -d "$storage_dir" -S file_collision --override='.*'
    ;;

# We can ignore subdirectories of our packages
--ignore)
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication --ignore 'an_application_other_subdir' --verbose 5
    ;;


# Demo with fresh directory, Things to note: After the first stow,
# $new_link_dir/bin will be a link pointing to ../storage/AnApplication/bin but
# after the second stow, since both packages have subdirectories called bin,
# stow will replace the link to ../storage/AnApplication/bin with a directory
# containing links to all the files in ../storage/AnApplication/bin and then
# will do the links for OtherApplication.
--fresh)
    stow -t "$new_link_dir" -d "$storage_dir" -S AnApplication
    echo "== First one =="
    tree -l $new_link_dir
    echo "== Second one ="
    stow -t "$new_link_dir" -d "$storage_dir" -S OtherApplication
    tree -l $new_link_dir
    ;;

## THIS ONE IS SUPPOSED TO FAIL
# This is because the second call needs to delete $storage_dir/bin
# to replace it with a directory containing links, however, it "belongs" to another storage location than the current one, so stow doesn't proceed with the second call.
--different-storage-fresh)
    stow -t "$new_link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$new_link_dir" -d "$other_storage_dir" -S OtherApplication
    ;;

# If stow doesn't have to delete anything, we can install things from different storage locations.
# So crating empty directories is one way of supporting installation from different stroage locations.
--different-storage)
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$other_storage_dir" -S OtherApplication
    ;;

# Override will not apply if things are from different storage locations.
--different-storage-override)
    stow -t "$link_dir" -d "$storage_dir" -S AnApplication
    stow -t "$link_dir" -d "$other_storage_dir" -S link_collision --override='.*'
    ;;

# This doesn't work
--same-ish-storage)
    stow -t "$new_link_dir" -d "$this_dir" -S storage/AnApplication
    stow -t "$new_link_dir" -d "$this_dir" -S other-storage/OtherApplication
    ;;

# But this does.  It's a directory containing links to storage/AnApplication and other-storage/OtherApplication.
--fake-common-storage)
    stow -t "$new_link_dir" -d "$this_dir/common" -S AnApplication
    stow -t "$new_link_dir" -d "$this_dir/common" -S OtherApplication
    ;;
*)
    echo "\$1 musta have a value in the case"
esac

