bubble-sort-by-ref(){
    local -n _in=${1}
    local tmp
    local i j

    for((j=${#_in[@]}-1;j>=0;j--)) ; do
        for((i=0;i<j;i++)); do
            if [[ ${_in[i]} > ${_in[i+1]} ]] ; then
                tmp="${_in[i]}"
                _in[i]=${_in[i+1]}
                _in[i+1]=${tmp}
            fi
        done
    done
}

selection-sort-by-ref(){
    local -n _in=${1}
    local i j tmp sorted

    for((j=${#_in[@]}-1;j>0;j--)) ; do
        i_max=0
        for((i=0;i<=j;i++)); do
            if [[ ${_in[i]} > ${_in[i_max]} ]] ; then
                i_max=$i
            fi
        done
        if ((i_max != j)) ; then
            tmp=${_in[j]}
            _in[j]=${_in[i_max]}
            _in[i_max]=${tmp}
        fi
    done
}

confirm-sorted-by-ref(){
    local -n _in=${1}
    for((i=0;i<${#_in[@]}-1;i++));do
        if [[ ${_in[i]} > ${_in[i+1]} ]] ; then
            return 1
        fi
    done
    return 0
}

confirm-algo(){
    local algo=${1}
    local src=(exit with the same status as COMMAND, even when the Mandatory
        COMMAND to read from the TTY and get TTY signals in this mode, children)
    if [[ ${algo} == "b" ]] ; then
        bubble-sort-by-ref src
    else
        selection-sort-by-ref src
    fi
    confirm-sorted-by-ref src
}

timing-test(){
    local algo=${1:-}
    n_iter=10
    src=(exit with the same status as COMMAND, even when the Mandatory
        arguments to long options are mandatory for short options too allow
        COMMAND to read from the TTY and get TTY signals in this mode, children
        of COMMAND will not be timed out If the command times out, and
        --preserve-status is not set, then exit with status 124.  Otherwise,
        exit with the status of COMMAND.  If no signal is specified, send the
        TERM signal upon timeout.  The TERM sig‐ nal kills any process that
        does not block or catch that signal.  It may be necessary to use the
        KILL 9 signal, since this signal cannot be caught, in which case the
        exit status is 128+9 rather than 124)
    src=("${src[@]}" "${src[@]}")

    if [[ $1 == b* ]] ; then
        printf "Bubble\n"
        time for((i=0; i<${n_iter} ; i++)) ; do
            m=("${src[@]}")
            bubble-sort-by-ref m
        done
    else
        printf "Selection\n"
        time for((i=0; i< ${n_iter}; i++)) ; do
            m=("${src[@]}")
            selection-sort-by-ref m
        done
    fi
}

# confirm-algo "b"
# confirm-algo ""

timing-test "b"
timing-test ""
