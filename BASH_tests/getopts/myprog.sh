#!/usr/bin/env bash

# Leading ':' => silent error reporting
# - Unknown option:   the_opt='?', OPTARG=${the_unknown_option}
# - Missing argument: the_opt=':', OPTARG=${the_option_missing_an_arg}

# Note that the question mark is a globbing character, if we had
#
#     `?) echo "The option ${OPTARG} is unknown"`
#
# but we forget to include a `x)` case, then we would enter the `?)` and print
# `The option  is unknown` so to distinguish between an unknown option that is
# not in OPTSTRING and a valid option that is in OPTSTRING but for which we
# forgot to include a case we include both `'?')` and `?)` cases.
#
# In real applications, I would probably just have a `?)` case but I would know
# that if I see something like `The option  is unknown`, then it means I forgot
# to add a case for some option.
#
vegetable=None
fruit=None
yes=false
x="I forgot the case"
while getopts ":yf:v:x" the_opt "$@" ; do
    case ${the_opt} in
        f)   fruit=${OPTARG} ;;
        v)   vegetable=${OPTARG} ;;
        y)   yes=true ;;
        :)   echo "The option -${OPTARG} requires an argument" ; exit 2 ;;
        '?') echo "The option -${OPTARG} is unknown" ; exit 2 ; ;;
        ?)   echo "The option ${the_opt} is valid but is not handled by the programmer" ; exit 5 ;;
    esac
done
declare -p vegetable fruit yes x

shift $((OPTIND-1))
posargs=("$@")
declare -p posargs


