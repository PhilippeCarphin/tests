#!/bin/bash

# This test shows that the construct $# applies to functions as well as with
# scripts.  Also, if a string contains spaces, passing that string to a function
# will result in mutliple argumens. However if we use quotes, then just one.

function echo_args(){
	n_args=$#
	echo "number of args : $n_args"
	while [[ $# -gt 0 ]]
	do
		echo $1
		shift
	done
}

echo_args a b c d # Function will have four arguments

args="allo bonjour"
echo "args=$args"

echo_args $args # Function will have two arguments
echo_args "$args" # Function will have one argument

