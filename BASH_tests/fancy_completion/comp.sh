#!/usr/bin/env bash
log(){
    printf "%s\n" "$*" >> ~/.log.txt
}
#
# This file demonstrates how we can output information during completion
# without messing up what the user sees.
#
# This basically works by manually reprinting the prompt and the currnt line
# $COMP_LINE if necessary.  This is shown with the fruits (-f) and the
# comp_message function.
# - COMP_TYPE=1 means single tab where.  If we have printed a message, then
#   we need to reprint
# - COMP_TYPE=63 means double-tab where BASH prints all the candidates and
#   automatically reprints the line and the prompt so in that case we don't
#   need to reprint the prompt and line.
#
# One reason why printing during completion might be desired is when getting
# the candidates takes a long time.  In that case it might be nice to show
# some indication that work is being done.
#
# The completions for the other options -c, -v, -V show ideas for such output.
#
# This was inspired by looking at how fzf works.  It turns out that it works
# by doing lots of manual work with cursor manipulation and ANSI codes.
comp_this_dir=$(cd -P $(dirname ${BASH_SOURCE[0]}) && pwd)

comp_message(){
    printf "\n\033[35mNOTE\033[0m:%s" "$*"
    comp_message_printed=1
}

_c(){
    local comp_message_printed=0
    COMPREPLY=()
    local prev="${COMP_WORDS[COMP_CWORD-1]}"
    case "${prev}" in
        -f)
            comp_message "Completing fruits"
            COMPREPLY=( $(compgen -W "apple apricot cherry bananna" -- "${COMP_WORDS[COMP_CWORD]}"))
            ;;
        -F)
            # See ~/.fzf/shell/completion.bash: _fzf_proc_completion as a more complete example
            # of how to use fzf to supercharge completion.  Note that fzf completion in that
            # case only goes if [[ cur == *'**' ]]
            result=$(printf "APPLE\nAPRICOT\nBANANNA\nCHERRY\n" | fzf --query "${COMP_WORDS[COMP_CWORD]}")
            COMPREPLY=($result)
            ;;
        -c)
            comp_acquire_candidates_spinner
            ;;
        -v)
            acquire_candidates_dots_in_loop
            ;;
        -C)
            result=$(${comp_this_dir}/square_choices.sh RED ORANGE YELLOW GREEN BLUE INDIGO VIOLET)
            # I made the square_choices script so that it could be used as a standaloe command
            # so this here is necessary to adapt it to use in completion
            printf "\033[A\r%s%s" "${PS1@P}" "${COMP_LINE}"
            COMPREPLY=($result)
            ;;
        -Z) result=$(${comp_this_dir}/square_choices.sh A B C D E F G H I J K L M N O P Q R S T U V W X Y Z)
            # Same adaptiation as for -C
            printf "\033[A\r%s%s" "${PS1@P}" "${COMP_LINE}"
            COMPREPLY=($result)
            ;;
        -V)
            acquire_candidates_spinner_in_loop
            ;;
        *) COMPREPLY=($(compgen -W "-f -F -c -v -C -Z -V" -- "${COMP_WORDS[COMP_CWORD]}"))
    esac
    if [[ ${COMP_TYPE} == 9 ]] && [[ ${comp_message_printed} == 1 ]] ; then
        printf "\n%s" "${PS1@P}"
        printf "%s" "${COMP_LINE}"
    fi
}

comp_spinner(){
    local spinner=('-' '\' '|' '/')
    local i=0
    while true ; do
        printf "%s\033[1D" "${spinner[++i%4]}"
        sleep 0.5
    done
}
comp_cached_colors=()
comp_acquire_candidates_spinner(){
    if [[ ${#comp_cached_colors[@]} == 0 ]] ; then
        printf "\033[?25l"
        printf "\nAcquiring completion candidates "
        comp_spinner &
        local sp=$!
        printf "\033[?25l"
        for i in red orange yellow green blue indigo violet; do
            comp_cached_colors+=("$i")
            sleep 0.2
        done
        printf "\033[?25h"
        comp_message_printed=1
        kill $sp
    fi
    COMPREPLY=($(compgen -W "${comp_cached_colors[*]}" -- "${COMP_WORDS[COMP_CWORD]}"))
}

comp_cached_VEGETABLES=()
acquire_candidates_spinner_in_loop(){
    # Perhaps some other condidtion to detect that we need to re-get the candidates
    local spinner=('-' '\' '|' '/')
    if [[ ${#comp_cached_VEGETABLES[@]} == 0 ]] ; then
        printf "\033[?25l"
        printf "\nacquiring candidates "
        # If it's long because we're thousands of candidates, that each take
        # 1ms, then we can print a '.' every 500 iterations.
        local i=0
        for v in POTATO CARROT TOMATO CUCUMBER ; do
            printf "%s\033[1D" "${spinner[i++%4]}"
            comp_cached_VEGETABLES+=("$v")
            sleep 1
        done
        comp_message_printed=1
    fi
    COMPREPLY=($(compgen -W "${comp_cached_VEGETABLES[*]}" -- "${COMP_WORDS[COMP_CWORD]}"))
    printf "\033[?25h"
}

comp_cached_vegetables=()
acquire_candidates_dots_in_loop(){
    # Perhaps some other condidtion to detect that we need to re-get the candidates
    if [[ ${#comp_cached_vegetables[@]} == 0 ]] ; then
        printf "\033[?25l"
        printf "\nacquiring candidates "
        # If it's long because we're thousands of candidates, that each take
        # 1ms, then we can print a '.' every 500 iterations.
        for i in potato carrot tomato cucumber ; do
            comp_cached_vegetables+=("$i")
            sleep 1
            printf "."
        done
        printf "\033[?25h"
        comp_message_printed=1
    fi
    COMPREPLY=($(compgen -W "${comp_cached_vegetables[*]}" -- "${COMP_WORDS[COMP_CWORD]}"))
}


c(){
    print_args "$@"
}

complete -F _c c

