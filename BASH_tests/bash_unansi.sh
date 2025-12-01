#
# This demonstrates the use of `coproc` to get an unansifying coprocess
# that just sits there and waits for input to unansify
#
repl='s/\x1b\[[0-9;]*m//g';

main(){
    # We have an array of strings that contain no newlines
    readarray -t files < <(ls --color=always -lhrt)

    # We want to produce a companion array that is the non-ansi version of each
    # string.  In this case, we could do
    # `readarray -t files_noansi < <(ls --color=false -lhrt)`
    # but that's not the idea.

    # Ideally we would want to send all our stuff to sed one-shot and retrieve
    # it oneshot like `readarray -t new_array < <( ??? | sed ${repl})`
    # but when going from array to array, the form
    # for x in "${array_x[@]}" ; do
    #      y=???
    #      array_y[i++]="$y"
    # done
    # is much easier.  How do we take x and unansi it?
    unset files[0]
    local x y i=0 files_noansi=()
    if [[ -z $1 ]] ; then
        # The naïve way of doing it, just launch sed every time.  The act of
        # performing the replacement is so quick that forking and excec-ing is most
        # of the work.
        for x in "${files[@]}" ; do
            printf -- "      %s\n" "$x"
            y=$(echo "$x" | sed ${repl})
            printf -- "  ==> %s\n" "$y"
            files_noansi[i++]="$y"
        done
    elif [[ $1 == coproc ]] ; then
        # Using coproc, we have sed running in the background just sitting there
        # waiting for us to have it perform replacements.
        coproc unansi { sed --unbuffered ${repl} ; }
        for x in "${files[@]}" ; do
            echo "$x" >&${unansi[1]}
            read y <&${unansi[0]}
            files_noansi[i++]="$y"
        done
    elif [[ ${1} == fifo ]] ; then

        if ! fifo_tmpdir=$(mktemp -d) ; then exit 1 ; fi
        trap "rm -rf ${fifo_tmpdir}" EXIT
        mkfifo ${fifo_tmpdir}/in_data ${fifo_tmpdir}/out_data
        command <${fifo_tmpdir}/in_data sed --unbuffered ${repl} >${fifo_tmpdir}/out_data &
        exec {to_sed}>${fifo_tmpdir}/in_data
        exec {from_sed}<${fifo_tmpdir}/out_data

        for x in "${files[@]}" ; do
            echo "$x" >&${to_sed}
            read y <&${from_sed}
            files_noansi[i++]="$y"
        done
    elif [[ $1 == bash-re-ref ]] ; then
        for x in "${files[@]}" ; do
            unansi_by_ref x y
            files_noansi[i++]="$y"
        done
    elif [[ $1 == bash-re ]] ; then
        for x in "${files[@]}" ; do
            y="$(unansi "$x")"
            files_noansi[i++]="$y"
        done
    fi
    for((i=0;i<${#files[@]};i++)); do
        printf -- "      %s\n" "${files[i]}"
        printf -- "  ==> %s\n" "${files_noansi[i]}"
    done
}

unansi_by_ref(){
    # Thanks Charles Duffy: https://stackoverflow.com/a/22261454/5795941
    local -n var=$1
    local -n outvar=$2
    local tmp=${var}
    local regex=$'(.*)\033\[[0-9;]*m(.*)'
    while [[ "${tmp}" =~ $regex ]] ; do
        tmp=${BASH_REMATCH[1]}${BASH_REMATCH[2]}
    done
    outvar="${tmp}"
}
unansi(){
    # Thanks Charles Duffy: https://stackoverflow.com/a/22261454/5795941
    local tmp=$1
    local regex=$'(.*)\033\[[0-9;]*m(.*)'
    while [[ "${tmp}" =~ $regex ]] ; do
        tmp=${BASH_REMATCH[1]}${BASH_REMATCH[2]}
    done
    echo "$tmp"
}

main "$@"
