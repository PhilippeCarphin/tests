#!/usr/bin/env -S bash -o errexit -o nounset -o errtrace -o pipefail -O inherit_errexit -O nullglob -O extglob

command echo "PART ONE"

alias echo='echo "echo-alias"'
shopt -s expand_aliases
source setup.sh
shopt -u expand_aliases
a-function

command echo "PART TWO"
shopt -s expand_aliases
source setup.sh
alias echo='echo "new-echo-alias"'
a-function

command echo "PART THREE"
alias ls='ls --color'
shopt -s expand_aliases
source setup.sh
type do-ls
unalias ls
do-ls
