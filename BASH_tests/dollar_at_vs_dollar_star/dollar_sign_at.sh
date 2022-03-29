#!/bin/bash

echo $@

if [[ "$@" == "" ]] ; then
   echo "no arguments"
else
   echo "at least one arg"
fi

