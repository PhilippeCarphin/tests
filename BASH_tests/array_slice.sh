array_slice(){
    local -n array=$2
    local -i start end length
    local -ri array_length=${#array[@]}
    if [[ $1 == *:* ]]; then
        start=${1%:*} ; end=${1#*:}
        if [ -z "$end" ] ; then
            end=$array_length
        fi
        if (( end < 0 )) ; then
            end=array_length+end
        fi
        if [ -z "$start" ] ; then
            start=0
        fi
        if (( start < 0 )) ; then
            start=array_length+start
        fi
    else
        start="$1"
        if (( start < 0 )) ; then
            start=array_length+start
        fi
        end=start+1
    fi
    length=end-start
    # check bounds
    if (( length < 0 )) || (( start < 0 )) || (( start >= array_length )) ; then
        return 1
    fi

    if (( $# == 3 )) ; then
        local -n output=$3
        output=("${array[@]: $start:$length}")
    else
        echo "${array[@]: $start:$length}"
    fi
}
alias array.slice="array_slice"
