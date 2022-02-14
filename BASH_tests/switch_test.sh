#!/bin/bash

# ${1%%suffix} # Value of $1 with 'suffix' removed if present
# ${1##prefix} # Value of $1 with 'prefix' removed if present
# suffix and prefix can be be regular expressions so ${1%%[0-9]*} would remove
# any digits at the end of $1.

# ${1:-default} # Value of $1 if $1 is not '', otherwise 'default'

case ${1:---help} in
--help)
    echo "HELP"
    ;;
--doc)
    echo "DOC"
    ;;
*)
    echo "DEFAULT"
    ;;
esac

case $1 in
""|--help)
    echo "HELP"
    ;;
--doc)
    echo "DOC"
    ;;
*)
    echo "DEFAULT"
    ;;
esac
