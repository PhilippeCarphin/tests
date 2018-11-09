#!/bin/bash

# Change this to false to see why the 'if is_relative_link' part is necessary.
handle_relative_links=true

is_relative_link(){
    [[ $1 != /* ]]
}

# This finds the current directory of the file while resolving 
# ref https://stackoverflow.com/a/246128/5795941

# NOTE: This is BASH specific. The point of this script is to show what to do
# once you have a value of "this_file". For ZSH, this is different. See
# BASH_tests/detect_sourcing.sh for a more complete solution.

# NOTE: The #!/bin/bash solves the problem of worrying about ZSH but only if the
# script is being run. If it is sourced, then it will be ZSH that runs it, and
# so this line won't work.
this_file=${BASH_SOURCE[0]}

echo "Initial : this_file = $this_file"
ls -l $this_file
while [ -L $this_file ] ; do
    echo "==========================================================="
    curr_dir="$(cd -P "$(dirname $this_file)" > /dev/null && pwd)"
    this_file=$(readlink $this_file)
    echo "while link : this_file = $this_file"
    if $handle_relative_links ; then
        if is_relative_link $this_file ; then
            this_file=$curr_dir/$this_file
            echo "while link : correction for relative link:"
            echo "    this_file = $this_file"
        fi
    fi
    ls -l $this_file
done

echo "================== FINAL VALUES ==========================="
this_dir=$(cd -P $(dirname $this_file) > /dev/null && pwd)

echo " this_dir = $this_dir"
echo "this_file = $this_file"

# NOTE: The preceding gives a full path to the file after following all symlinks
# and resolving all the links in the path. If the file is somewhere in your
# project and you want to have the project root, you can do something like this:
echo "$(cd -P "$(dirname $this_file)/.." > /dev/null && pwd)"
