#!/bin/bash

source $HOME/Documents/GitHub/tests/BASH_tests/link_resolve/bin/the_script.sh

# This finds the current directory of the file while resolving 
# ref https://stackoverflow.com/a/246128/5795941

# NOTE: This is BASH specific. The point of this script is to show what to do
# once you have a value of "this_file". For ZSH, this is different. See
# BASH_tests/detect_sourcing.sh for a more complete solution.

# NOTE: The #!/bin/bash solves the problem of worrying about ZSH but only if the
# script is being run. If it is sourced, then it will be ZSH that runs it, and
# so this line won't work.
this_file=${BASH_SOURCE[0]}
echo "==================== Initial =============================="
echo "this_file = $this_file"

this_file=$(follow_links $this_file)

# Portable normalization (the -f option to readlink is not available on OSX)
this_file=$(cd -P "$(dirname $this_file)" && pwd)/$(basename $this_file)

echo "================== FINAL VALUES ==========================="
this_dir=$(cd -P $(dirname $this_file) > /dev/null && pwd)

echo " this_dir = $this_dir"
echo "this_file = $this_file"

# NOTE: The preceding gives a full path to the file after following all symlinks
# and resolving all the links in the path. If the file is somewhere in your
# project and you want to have the project root, you can do something like this:
# echo "$(cd -P "$(dirname $this_file)/.." > /dev/null && pwd)"

python_way=$(python -c "import os,sys; print(os.path.realpath(sys.argv[1]))" ${BASH_SOURCE[0]})
echo "Python way: $python_way"
