# Applying Thing from Dave Eddy (YSAP) setting the scrollable region

init-term(){
    local start=$1
    local end=$2
    shopt -s checkwinsize
    /usr/bin/true

    printf "INFO: LINES=${LINES}, COLUMNS=${COLUMNS}\n"
    sleep 1
    printf "\e[1A\e[0K====================================="
    n=$((LINES-start+1))
    s=''
    u=''
    for((i=0;i<n;i++)) ; do
        s+='\n'
    done
    printf "$s"
        sleep 2
        printf "\e7"
            # Set scrollable region
            printf "\e[%d;%dr"  "${start}" "${end}"
        printf "\e8"
    printf "\e[%d;0H" "${start}"
}

deinit-term(){
    printf "\e7"
        printf "\e[%d;%dr" 0 "${LINES}"
        printf "\e[%d;%dH" "${LINES}" 0
        printf "\e[0K"
    printf "\e8"
}

trap deinit-term EXIT
init-term 8 13

tree Repositories/github.com/philippecarphin/clojure-tasks | while read l ; do
    echo "${l}"
    sleep 0.3
done
