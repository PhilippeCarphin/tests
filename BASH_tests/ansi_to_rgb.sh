#!/bin/bash

map=(0 95 135 175 215 255)
# Code from [16,231] (code is 16 + 36r + 6g + b where r,g,b in [0,5])
# And [0,5] --map--> [0,255]
# [0,255]x[0,255]x[0,255] ---> [0,255] with 0.3*R + 0.59*G + 0.11*B
# [0,255] ---> [232,255] (range of grayscale ansi codes)
ansi_to_grayscale(){
    local ansi=$1
    if (( ansi < 16 )) ||((ansi > 231)) ; then
        return 1
    fi
    ansi=$((ansi-16))

    local b=$((ansi % 6))
    local g=$(( (ansi/6) % 6 ))
    local r=$(( (ansi/36) ))

    local gray=$(( (30*map[r] + 59*map[g] + 11*map[b]) / 100 ))
    local code=$((232 + (gray * (255-232))/255))
    echo "${code}"
}


ansi_to_grayscale "$@"
