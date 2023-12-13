#!/usr/bin/env bash
# Based on https://gist.github.com/Asher256/4c68119705ffa11adb7446f297a7beae
# Behavior is slightly modified, output is modified to look more like a Python
# exception traceback including the actual lines in the files.
#
# When the error is from a function doing 'return 1' the position of the return 1
# is not part of the traceback.
#
#     Bash traceback
#     
#     Because the option “set -o errexit” / "set -e" does not show any message
#     when it stops your Bash script in some cases (for example
#     var=$(yourcommand) will exit without any message, even when yourcommand
#     returns an exit code different from zero), I recommend you to add the
#     code below to your bash scripts to show a traceback each time “errexit”
#     forces your Bash script to stop.
#
#     License: MIT
#
#     Author: Asher256
#     Github: https://github.com/Asher256
#     Website: http://www.asher256.com/
#

set -o errexit    # stop the script each time a command fails
set -o nounset    # stop if you attempt to use an undef variable

function bash_traceback() {
  local lasterr="$?"
  set +o xtrace
  local code="-1"
  local bash_command=${BASH_COMMAND}
  echo "Traceback of ${BASH_SOURCE[1]} (most recent call last):" >&2
  if [[ -n ${DBG-} ]] ; then
    echo "FUNCNAME = ${FUNCNAME[*]}"
    echo "BASH_LINENO = ${BASH_LINENO[*]}"
    echo "BASH_SOURCE = ${BASH_SOURCE[*]}"
  fi
  for ((i=$((${#FUNCNAME[@]}-1)); i>0 ; i--)); do
      in_function=${FUNCNAME[$i]}
      at_lineno=${BASH_LINENO[$i-1]}
      in_file=${BASH_SOURCE[$i]}
      printf "   File \"%s\", line %d, in %s\n" ${in_file} ${at_lineno} ${in_function}
      l=($(get_line $in_file $at_lineno))
      printf "       %s\n" "${l[*]}"
  done
  echo "Command '$bash_command' returned $lasterr" >&2
}
get_line(){
    file=$1
    line=$2
    head -n $line $file | tail -n 1
}

# provide an error handler whenever a command exits nonzero
trap 'bash_traceback' ERR

# propagate ERR trap handler functions, expansions and subshells
set -o errtrace
