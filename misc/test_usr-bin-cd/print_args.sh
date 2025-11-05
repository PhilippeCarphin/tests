#!/bin/bash

echo "Number of args = $#"
for ((i=1;i<=$#;i++)) do
    printf "\$$i: '${!i}'\n"
done
