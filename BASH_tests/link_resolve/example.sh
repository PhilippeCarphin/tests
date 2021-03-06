#!/bin/bash


bootstrap_is_relative_link(){
    [[ $1 != /* ]] && [ -L $1 ]
}

bootstrap_follow_links()
{
    local file="$(cd -P "$(dirname $1)" > /dev/null && pwd)/$(basename $1)"
    local curr_dir="$(cd -P "$(dirname $file)" > /dev/null && pwd)"
    while [ -L $file ] ; do
        curr_dir="$(cd -P "$(dirname $file)" > /dev/null && pwd)"
        file="$(readlink $file)"
        if is_relative_link $file ; then
            file="$curr_dir/$file"
        fi
    done
    echo $file
}


this_example_file=$(bootstrap_follow_links ${BASH_SOURCE[0]})
this_example_dir=$(cd -P $(dirname $this_example_file) > /dev/null && pwd)

if ! source $this_example_dir/bin/the_script.sh ; then
    echo "ERROR : Could not source"
    exit
fi

# This finds the current directory of the file while resolving 
# ref https://stackoverflow.com/a/246128/5795941

# we have dir2/example.sh -> ../dir1/example.sh -> ../example.sh
# which happens to be this exact file.
this_file=$this_example_dir/links/link_to_file
echo "==================== Initial =============================="
echo "this_file = $this_file"

this_file=$(follow_links $this_file)

echo "================== FINAL VALUES ==========================="
this_dir=$(cd -P $(dirname $this_file) > /dev/null && pwd)
if [ -d $this_file ] ; then
    this_dir=$this_file
else
    this_dir=$(cd -P $(dirname $this_file) > /dev/null && pwd)
fi

echo " this_dir = $this_dir"
echo "this_file = $this_file"

echo '***************************************************************************'
this_file=$this_example_dir/links/link_to_dir
echo "==================== Initial =============================="
echo "this_file = $this_file"

this_file=$(follow_links $this_file)

# Portable normalization (the -f option to readlink is not available on OSX)
this_file=$(cd -P "$(dirname $this_file)" && pwd)/$(basename $this_file)

echo "================== FINAL VALUES ==========================="
if  [ -d $this_file ] ; then
    this_dir=$this_file
else
    this_dir=$(cd -P $(dirname $this_file) > /dev/null && pwd)
fi

performance(){
    echo "================================="
    echo "checking timing for $1 link chain"
    start_num=$((999-$1))
    start_link=${this_example_dir}/performance/link_${start_num}
    echo "----- bash function ------------"
    time follow_links ${start_link}
    echo "----- python code ------------"
    time python3 -c "import os,sys; print(os.path.realpath(sys.argv[1]))" ${start_link}
    if which true_path 1>/dev/null 2>&1 ; then
        echo "----- true_path program ------------"
        time true_path ${start_link}
    fi
}
performance 150
performance 10
performance 1
performance 2
performance 3
performance 4
performance 5
performance 6
performance 998

echo " this_dir = $this_dir"
echo "this_file = $this_file"
