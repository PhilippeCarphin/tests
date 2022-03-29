#!/bin/bash '"MUST BE SOUCED" ; exit 1'
echo "I sure hope I'm being souced"

oneliner=true


if $oneliner ; then
    (return 0 2>/dev/null) && sourced=true || sourced=false
    if ! $sourced ; then echo "No, really, this file must be sourced" ; exit 1 ; fi
else
    # From https://stackoverflow.com/a/28776166
    sourced=0
    if [ -n "$KSH_VERSION" ]; then
        zero_path="$(cd $(dirname -- $0) && pwd -P)/$(basename -- $0)"
        sh_file_path="$(cd $(dirname -- ${.sh.file}) && pwd -P)/$(basename -- ${.sh.file})"
        if [ "$zero_path" != "$sh_file_path" ] ; then
            sourced=true
        fi
    elif [ -n "$BASH_VERSION" ]; then
        if (return 0 2>/dev/null) ; then
            sourced=true
        else
            sourced=false
        fi
    fi
fi


if ! $sourced ; then
    echo "You fooled the shebang thing, but the return trick is infallible in BASH"
fi
