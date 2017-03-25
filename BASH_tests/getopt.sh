#!/bin/bash

# OPTION PARSING EXAMPLE WITH EXPLANATION
# Philippe Carphin Sat Mar 25 12:07:07 EDT 2017

# When we call a script, it's arguments are accessible with $0, $1, ...
# $0 is the name of the script itself, it's useful for other things but not
# useful here.
# $1 is the first argumtent, $2 is the second and so on ...
# The following while loop is self explanatory once one understands what
# 'shift' does: it shifts every variable in the arguments down by one. That
# means that $1 takes the value of $2, $2 takes the value of $3 and so on ...
# so say we have ./script.sh --option1 option1_arg --option2 option2_arg ...
# in the first pass we will have
#	./script.sh --my_option my_option_arg --option2 option2_arg ...
#                      $1        $2         $3        $4
# the shift in the -o|--my_option) is there because that option takes an
# argument. After that shift we have
#	./script.sh --my_option my_option_arg --option2 option2_arg ...
#                                  $1        $2         $3        $4
# Then at the end of the case statement there is another shift. This way, when
# we encounter an option that takes an argument two shifts will happen, and when
# we encounter an option that doesn't take an argument, only one shift will
# happen as with -f|--my_flag).

# When the option doen't begin with a '-' it could be considered a positionnal
# argument.  These arguments are accumulated in a variable posargs to be parsed
# separately later.

# If possible, I advise not to use positionnal arguments for scripts (because if
# you don't have positionnal arguments, a call to your script will be
# self-documenting which reduces the likelihood for erroneous calls to your
# script).

# However if you want to use them or if you have to, this is one way to do it.
# This way is similar to the way getopt() in C works.  It leaves the argv[]
# array containing only the positionnal arguments.

# This script shows an elementary parsing method for argumens
# Normally scripts like this don't have postionnal arguments but one might wish
# to have them so I give one method to accumulate them into a variable named
# posargs.  Then two methods for parsing that variable.

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
			shift # Extra shift for options that take an argument
			;;
		-f|--my_flag)
			my_flag=true
			# no extra shift for options that don't take an argument
			;;
        -*)
            echo "unknown option: $option"
            exit
			;;
		*)
			posarg=$option # The option is acutally a posarg
			posargs="$posargs $posarg"
			;;
    esac
shift # Alwasys shift once
done

# The first method for parsing posargs is simply to put each posarg in the right
# variable since their position indicates their role.
function parse_posargs(){
	file=$1
	date=$2
	mood=$3
}

parse_posargs $posargs
# TEST : ./getopt.sh a_file -f today --my_option my_optarg happy

# For positionnal arguments, one might want to do something custom like cp for
# example.  If it has n posargs, the n-1 first are the files to copy and the
# last one is the destination.

function parse_posargs_custom(){
	while [[ $# -gt 1 ]]
	do
		files_to_copy="$files_to_copy $1"
		shift
	done
	destination=$1
}
parse_posargs_custom $posargs

# TEST: run this commands:
# ./getopt file1 file2 -f --my_option my_optarg file3 file4 destination

# Normally, all functions would be declared at the top then we would have the
# main parsing of arguments then we would call our parsing function, then it is
# recommended to check the validity of the arguments and options, and then our
# script.

echo "my_option = $my_option_arg"
echo "my_flag = $my_flag"
echo "file = $file"
echo "date = $date"
echo "mood = $mood"
echo "files_to_copy = $files_to_copy"
echo "destination = $destination"



