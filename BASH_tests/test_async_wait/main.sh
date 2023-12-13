exit_traps=()
trap 'for t in "${exit_traps[@]}" ; do eval $t ; done' EXIT

function timed_fail(){
    local time=$1
    local output_file=$2

    for ((i=0;i<$time;i++)) ; do
        echo "timed_fail $i" >> ${output_file}
        sleep 1
    done

    return $((time % 2))
}


main(){
    local output_file=output.txt

    echo > ${output_file}
    exit_traps+=("rm -f ${output_file}")
    timed_fail ${1-4} ${output_file} &
    timed_fail_pid=$!
    echo "timed_fail_pid=${timed_fail_pid}"

    noexist -f output.txt &
    local tail_pid=$!
    echo "tail_pid=${tail_pid}"
    exit_traps+=("kill ${tail_pid}")

    exit_traps+=("echo exit trap 3")
    if ! wait $timed_fail_pid ; then
        echo "timed_fail failed"
        return 42
    fi
}

main "$@"
