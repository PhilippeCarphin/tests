# fzf-file-widget is a function
# fzf-file-widget () 
# { 
#     local selected="$(__fzf_select__ "$@")";
#     READLINE_LINE="${READLINE_LINE:0:$READLINE_POINT}$selected${READLINE_LINE:$READLINE_POINT}";
#     READLINE_POINT=$(( READLINE_POINT + ${#selected} ))
# }
# __fzf_select__ is a function
# __fzf_select__ () 
# { 
#     local cmd opts;
#     cmd="${FZF_CTRL_T_COMMAND:-"command find -L . -mindepth 1 \\( -path '*/\\.*' -o -fstype 'sysfs' -o -fstype 'devfs' -o -fstype 'devtmpfs' -o -fstype 'proc' \\) -prune     -o -type f -print     -o -type d -print     -o -type l -print 2> /dev/null | cut -b3-"}";
#     opts="--height ${FZF_TMUX_HEIGHT:-40%} --bind=ctrl-z:ignore --reverse ${FZF_DEFAULT_OPTS-} ${FZF_CTRL_T_OPTS-} -m";
#     eval "$cmd" | FZF_DEFAULT_OPTS="$opts" $(__fzfcmd) "$@" | while read -r item; do
#         printf '%q ' "$item";
#     done
# }
#
tw(){
    print-args "$@" >> ~/.log.txt
    printf "READLINE_LINE='%s'\n" "${READLINE_LINE}" >> ~/.log.txt
    local rl_args=(${READLINE_LINE})
    if [[ "${READLINE_LINE}" == *' ' ]] ; then
        rl_args+=('')
    fi
    local dir=${rl_args[-1]:-$PWD}
    print-array rl_args >> ~/.log.txt
    local result=$(tui-selector ${dir})
    rl_args[-1]=${result}
    READLINE_LINE="${rl_args[*]}"
    READLINE_POINT=0xffffffff
}


