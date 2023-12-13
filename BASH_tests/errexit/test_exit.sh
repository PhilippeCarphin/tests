#!/bin/bash

set -o errexit # set -e
set -o pipefail
# set -o errtrace # set -E
trap 'echo "exit_trap triggered"' EXIT
trap 'echo "err_trap triggered"' ERR

for a in $(echo allo | ./exitter.sh 1) ; do
    echo $a
done
echo 'After "for a in $(echo allo | ./exitter.sh 1)"'

# Doesn't cause exit no matter what
for a in $(ls noexist) ; do
    echo $a
done
echo 'After "for a in $(ls noexist)"'
#
# The 'ls noexist' in do_stuff triggers an exit because 'errexit' is set
# however the trap on ERR is only executed if 'errtrace' (set -E) is set.
#
# do_stuff(){
#     ls noexist
#     echo 'do_stuff'
# }
# 
# do_stuff

#
# This will trigger an exit only if BOTH errexit and pipefail are ON because
# the command that fails is not the last one in the pipeline
#
list=$(echo allo | ./exitter.sh 1 | echo allo)
for a in $list; do
    echo $a
done
echo 'after for a in $list with "list=$(echo allo | ./exitter.sh 1 | echo allo)"'

#
# Only needs errexit to be ON to trigger an exit because in this case, the
# the command that fails is the last one of the pipeline.
#
list=$(echo allo | ./exitter.sh 1)
for a in $list; do
    echo $a
done
echo 'after for a in $list with "list=$(echo allo | ./exitter.sh 1)"'

