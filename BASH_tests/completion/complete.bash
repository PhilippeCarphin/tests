_log(){
    printf "$@\n" >> ~/.log.txt
}

_complete_func(){
    _log "==========================================="
    _log "\$1 = $1" # COMMAND
    _log "\$2 = $2" # CURRENT WORD
    _log "\$3 = $3" # PREVIOUS WORD
    _log "\$4 = $4" # NOTHING
    _log "\$COMP_WORDS[@] = ${COMP_WORDS[*]}"
    _log "\$COMP_CWORD = ${COMP_CWORD}"
    _log "\$COMP_LINE = ${COMP_LINE}"
    _log "\$COMP_POINT = ${COMP_POINT}"
    _log "\$COMP_KEY = ${COMP_KEY}"
    _log "\$COMP_TYPE = ${COMP_TYPE}"
    _log "\$x = ${x}"
    _log "\$x = ${x}"

    COMPREPLY=(apple apricot bananna cherry)
}

complete -F _complete_func cmd
complete -C $PWD/complete.py cm
