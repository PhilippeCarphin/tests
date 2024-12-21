#!/bin/bash

trap 'ls
boobs
booggers' EXIT
OIFS="${IFS}"
IFS=" "
exit_trap="$(eval a=($(trap -p EXIT)) ; echo "${a[2]}")"
IFS="${OIFS}"
echo "====== exit trap ========"
echo "${exit_trap}"
echo "========================="
trap - EXIT
