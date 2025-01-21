sep-join-tokens(){
    if (( ${#1} > 1 )) ; then
        echo "Joining using \$* only works for a single joining character" >&2
        return 1
    fi
    local IFS=$1 ; shift
    echo "$*"
}

colon-join(){
    sep-join-tokens ':' "$@"
}

LD_LIBRARY_PATH=""
SSMUSE_LD_PREPEND=/lib64

export LD_LIBRARY_PATH=$(colon-join ${SSMUSE_LD_PREPEND} ${LD_LIBRARY_PATH})

echo "LD_LIBRARY_PATH=${LD_LIBRARY_PATH}"
