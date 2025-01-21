# Extrace pieces from a string using regexes
# I called it sscanf because it helps to do things that would be done with
# sscanf (extract typed pieces from a string) but it doesn't have the same
# interface as sscanf.
# $ sscanf "1 2 abc" "([0-9]+) ([0-9]+) ([a-z])"
# $ declare -p BASH_REMATCH
# declare -ar BASH_REMATCH=([0]="1 2 34" [1]="1" [2]="2" [3]="34")
sscanf () {
    local regex="$2"
    echo "regex=${regex}"
    # local str="${1//+(${regex})/(.*)}"
    # echo "str=${str}"
    echo "1=$1"
    [[ $1 =~ ${regex} ]]

    if [[ ${#BASH_REMATCH[@]} == 1 ]] ; then
        local -n varname=$3
        varname=${BASH_REMATCH[0]}
    else
        shift ; shift ;
        for m in "${BASH_REMATCH[@]:1}" ; do
            if (( $# == 0 )) ; then
                echo "Not enough variable names for matches"
                break
            fi
            local -n varname=$1 ; shift
            varname="${m}"
        done
    fi
}
