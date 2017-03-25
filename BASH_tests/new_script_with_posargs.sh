#!/bin/bash

function parse_posargs(){
	file=$1
	date=$2
	mood=$3
}

function parse_posargs_custom(){
	while [[ $# -gt 1 ]]
	do
		files_to_copy="$files_to_copy $1"
		shift
	done
	destination=$1
}

my_option_arg=default_value
my_flag=false
posargs=""
while [[ $# -gt 0 ]]
do
    option="$1"
	optarg="$2"
    case $option in
        -o|--my_option)
			my_option_arg="$optarg"
			shift
			;;
		-f|--my_flag)
			my_flag=true
			;;
        -*)
            echo "unknown option: $option"
            exit
			;;
		*)
			posarg=$option
			posargs="$posargs $posarg"
			;;
    esac
shift
done

parse_posargs $posargs
parse_posargs_custom $posargs
