#!/bin/bash

if ! (return 0 2>/dev/null) ; then
    echo "File must be sourced" >&2
    exit 1
fi

alias an-alias='echo This is an alias'

function a-function(){
    shopt -p expand_aliases || true
    echo 'This is a function'
}

function do-ls(){
    ls "$@"
}
