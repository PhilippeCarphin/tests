#!/bin/bash

set -o errexit # set -e
set -o pipefail

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
