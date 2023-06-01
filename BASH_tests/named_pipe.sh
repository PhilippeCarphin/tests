#!/bin/bash

#
# This test demonstrates the use of named pipes in BASH.
#
# Note the use of a temporary directory.  This is the safer way of creating
# a named pipe.  This is because we need to come up with a name that is
# garanteed to not exist.  Using mktemp to give a non-existing filename
# without creating it creates a race condition where the file could get created
# after mktemp gave us the name but before we create the named pipe.
#
# Therefore, as suggested by a stack overflow post, the simple way to avoid
# this problem is to use mktemp -d to create a directory and create the named
# pipe inside.
#
# Reference for safety stuff : https://unix.stackexchange.com/a/29918/161630
#

script='
while read l ; do
    printf "got line \033[1;35m%s\033[0m\n" "$l"
done
'

cleanup(){
    echo "Running cleanup" >&2
    trap - EXIT
    if [[ -n "${tmpdir}" ]] ; then
        rm -rf "${tmpdir}"
    fi
    # The reference has extra stuff but this demo doens't
    # need an elite level of portability.
}
trap 'cleanup' EXIT HUP TERM


if ! tmpdir=$(mktemp -d) ; then
    echo "Error creating temporary directory"
    exit 1
fi


fifo_name=${tmpdir}/fifo
mkfifo ${fifo_name}
echo "fifo_name = '${fifo_name}'"

#
# Keep the pipe open otherwise, the following 'cat' command would reach EOF,
# which would close the pipe in the cat | bash command, and the script would
# stop.
#
# The example I found said to do this but it doesn't seem to change the
# behavior if I don't do it.
#
# sleep infinity > ${fifo_name} &
# sleep_pid=$!
#

cat ${fifo_name} | bash -c "${script}" &
bg_pid=$!

echo "hello" > ${fifo_name}
echo "world" > /proc/${bg_pid}/fd/0
echo "goodbye" > ${fifo_name}

# We could reach the end of *this* script before the 'hello' and 'world'
# are printed and we want the trap's prints to go at the end
sleep 0.1
