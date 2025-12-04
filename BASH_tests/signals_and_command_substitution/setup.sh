#!/usr/bin/env bash
this_dir=$(cd -P $(dirname ${BASH_SOURCE[0]}) && pwd)

sel-bad(){
    local result
    result=$(${this_dir}/selector.sh)
    # No matter what I do, this code is never run if I press C-c while it's
    # selector.sh is waiting for characters.
    printf "${FUNCNAME[0]}: The result of your selection is %q and the selector exited with $?\n" "${result}" >&2
    READLINE_LINE=${READLINE_LINE}${result}
    READLINE_POINT=0x7fffffff
}

sel-desired(){
    local f=$(mktemp)
    ${this_dir}/selector.sh >$f
    local selector_status=$?

    # This code gets executed after C-c only if I add the trap `trap 'exit 130' INT`
    # which makes it so this shell things the child was not killed by a signal
    read -N 1 result <$f
    printf "${FUNCNAME[0]}: The result of your selection is %q and the selector exited with ${selector_status}\n" "${result}" >&2
    READLINE_LINE=${READLINE_LINE}${result}
    READLINE_POINT=0x7fffffff
}

sel-fzf(){
    local result
    result=$(ls -l | fzf --height=20%)
    # I'm not doing anything different in the calling shell but there's something
    # about fzf that makes it so that pressing C-c while in $(... fzf ...)
    # is different than in sel-bad and the code below does always get run.
    printf "${FUNCNAME[0]}: The result of your selection is %q and the selector exited with $?\n" "${result}" >&2
    READLINE_LINE=${READLINE_LINE}${result}
    READLINE_POINT=0x7fffffff
}

bind -x '"\C-t": sel-bad'
bind -x '"\C-e": sel-desired'
bind -x '"\C-k": sel-fzf'
