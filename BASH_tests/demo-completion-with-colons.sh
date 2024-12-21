#!/bin/bash

################################################################################
# Complete paths starting with ':' starting from the root of the current git
# repository.  This is an alternate version that I made to figure out how to
# use deal with completing words that contain colons.  The first one is easier
# since we just deal with the part after the colon separately and return
# candidates for the part that comes after the colon.  This one is not so
# hard either.
################################################################################
_git_cd_with_colons(){
    local top IFS='
'
    compopt -o filenames
    if ! top="$(git rev-parse --show-toplevel)" ; then
        return
    fi

    # Local is very important otherwise full_words and full_cword would
    # become global variables that would grow every time __reassemble_comp_words_by_ref
    # is called.  I could also do '_init_completion -n :'.  Either way the call
    # to __ltrim_colon_completion is required at the end.
    local full_words full_cword;
    __reassemble_comp_words_by_ref ':' full_words full_cword || return

    local cur=${full_words[full_cword]}

    if [[ "${cur}" == ":" ]] ; then
        # Could also do COMPREPLY=("/") and not do __ltrim_colon_completions ':'
        # but this is more explicit
        COMPREPLY=(":/")
        __ltrim_colon_completions ':'
        return
    fi

    if ! [[ "${cur}" == :* ]] ; then
        return
    fi

    local -r mark_dirs=$(_rl_enabled mark-directories && echo y);
    local -r mark_symdirs=$(_rl_enabled mark-symlinked-directories && echo y);
    full_cur=${top}${cur#:}
    candidates=($(compgen -d -- ${full_cur}))
    local i=0
    for full_path in "${candidates[@]}" ; do
        relative_path=:${full_path##${top}}
        COMPREPLY[i++]=${relative_path}
    done

    # Add slash if we have only one completion and it is the full word
    # Lifted from _cd and changed to just always append the slash if
    # there is only one completion candidate.
    if ((${#COMPREPLY[@]} == 1)); then
        COMPREPLY[0]+=/;
    fi;

    __ltrim_colon_completions ':'
}
