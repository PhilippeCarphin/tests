#!/bin/bash

while IFS=',' read a b c d rest ; do
    echo "a='${a}', b='${b}', c='${c}', d='${d}', rest='${rest}'"
done < input.txt
