#!/usr/bin/env bash

# This script reads STDIN and sends it to a file but the same principle applies
# if we were reading it to a variable.

if (( $# < 2 )) ; then
    echo "$0 [cat|read] OUTPUT_FILE"
    exit 1
fi

case "$1" in
    cat) cat > "$2" ;;
    read) IFS=''
          while read line ; do
              echo "$line"
          done > "$2" ;;
esac
