filter_stdout(){
    local l
    while read l ; do
        printf "\033[32mSTDOUT: %s\033[0m\n" "${l}"
    done
}

filter_stderr(){
    local l
    while read l ; do
        printf "\033[31mSTDERR: %s\033[0m\n" "${l}"
    done < $1
}

filter_stderr $1 &
filter_stdout

wait
