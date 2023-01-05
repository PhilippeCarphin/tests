#!/bin/bash
#
# set -o errexit
# This script demonstrates the use of a trap on the ERR signal as inspired
# by https://gitlab.science.gc.ca/cmdw-spooki/c-ezinterpv90/blob/master/lib/make_ssm_packages.sh
#
# In this example, we have the trap exit the script which makes this kind of
# like using 'set -o errexit'.
#
# It's a pretty cool technique.  There are no downsides to using it but it
# does behave weirdly in some cases and not the way we would like in others.
# - It runs twice for assignments of the form 'list=$(generate_list)'
#   where generate_list returns 1 and the second time stops the program.
# - It does run in 'for item in $(generate_list); do' where generate_list
#   returns 1 but does not stop the program.
#
# All this requires the 'set -E' option to be used so that functions also
# 'inherit' the error trap.

set -E
shopt -s extdebug
trap 'errmsg ${LINENO} $?' ERR
errmsg()
{
  local MYSELF="$0"    # Equals to my script name
  local LAST_LINE="$1"  # Last line of error occurence
  local LASTERR="$2"   # Error code of last command
  echo "Error: ${MYSELF}:${LAST_LINE}:" >&2
  echo "    In function '${FUNCNAME[1]}'" >&2
  for f in "${FUNCNAME[@]:2}" ; do
      echo "    called by '$f'" >&2
  done
  exit ${LASTERR}
}

source bash-traceback.sh

source library.sh

function returner(){
    return $1
}

function philmain(){

    returner 0

    #
    # Causes the trap to run
    #
    # returner 31

    #
    # Does not cause the trap to run.
    # Normal since in this context the 'keep_going' return
    # value is used as a boolean for a decision
    #
    # while keep_going ; do
    #     true
    # done

    #
    # Causes the trap to launch but does not stop the script
    #
    # for i in $(ls noexist) ; do
    #     echo "i=$i"
    # done

    #
    # Launches the trap but the exit in the trap function does
    # not stop the script.
    #
    # for i in $(returner 31) ; do
    #     echo "i=$i"
    # done
    library_returner 11

    #
    # This does launch the trap.  The trap runs twice and it
    # does interrupt the script.
    #
    list=$(returner 88)

    #
    # This line causes the trap to run but the line number given
    # is the number for the line 'function philmain(){'
    #
    (exit 3)

    #
    # This does launch the trap same as 'for i in $(returner 1)
    #
    for i in $(generate_list) ; do
        echo "i=$i"
    done

    #
    # Calling exit in a subshell behaves weirdly in for loops: This does
    # not trigger the trap at all.
    #
    for i in $(returner 38) ; do
        echo "i=$i"
    done

    echo "end of ${FUNCNAME[0]}"
}

global_value=3
function keep_going(){
    if ((global_value--)) ; then
        return 0
    else
        return 1
    fi
}

function generate_list(){
    echo "1 2 3 4"
    return 27
}




philmain
