#!/bin/bash

letters="a b c d"

set $letters
echo "\$@ = $@"
echo "\$letters = $letters"
printf "\nfor l in \"\$@\"\n"
for l in "$@" ; do
    echo "    l : $l"
done
echo "for l in \"\$letters\""
for l in "$letters" ; do
    echo "    l : $l"
done
