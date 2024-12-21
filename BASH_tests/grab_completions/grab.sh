#!/bin/bash

source /opt/homebrew/share/bash-completion/bash_completion
source /opt/homebrew/share/bash-completion/completions/make
source ~/.git-completion.bash

COMP_WORDS=(git "")
COMP_CWORD=1 # The index of the word containing the cursor (the C is for cursor, not count)
COMP_LINE="make "
COMP_POINT=${#COMP_LINE}
COMP_TYPE=9
COMP_KEY=$'\t'
COMPREPLY=()
__git_wrap__git_main git "" git
for comp in "${COMPREPLY[@]}" ; do
    echo "$comp is one of the completion candidates"
done
