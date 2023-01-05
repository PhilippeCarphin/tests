#!/usr/bin/env bash
#
# Bash traceback
# 
# Because the option “set -o errexit” / "set -e" does not show any message when
# it stops your Bash script in some cases (for example var=$(yourcommand) will
# exit without any message, even when yourcommand returns an exit code
# different from zero), I recommend you to add the code below to your bash scripts
# to show a traceback each time “errexit” forces your Bash script to stop.
#
# License: MIT
#
# Author: Asher256
# Github: https://github.com/Asher256
# Website: http://www.asher256.com/
#

set -o errexit    # stop the script each time a command fails
set -o nounset    # stop if you attempt to use an undef variable

function bash_traceback() {
  local lasterr="$?"
  set +o xtrace
  local code="-1"
  local bash_command=${BASH_COMMAND}
  echo "FUNCNAME[@] = ${FUNCNAME[@]}"
  echo "Error in ${BASH_SOURCE[1]}:${BASH_LINENO[0]} ('$bash_command' exited with status $lasterr)" >&2
  if [ ${#FUNCNAME[@]} -gt 2 ]; then
    # Print out the stack trace described by $function_stack
    echo "Traceback of ${BASH_SOURCE[1]} (most recent call last):" >&2
    for ((i=0; i < ${#FUNCNAME[@]} - 1; i++)); do
        local funcname
        if [ "$i" -eq "0" ] ; then
            funcname=$bash_command
        else
            funcname="${FUNCNAME[$i]}"
        fi
        echo -e "  ${BASH_SOURCE[$i+1]}:${BASH_LINENO[$i]}\\t$funcname" >&2
    done
  fi
  echo "Exiting with status ${code}" >&2
  exit "${code}"
}

# provide an error handler whenever a command exits nonzero
trap 'bash_traceback' ERR

# propagate ERR trap handler functions, expansions and subshells
set -o errtrace
