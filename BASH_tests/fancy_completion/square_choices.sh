#!/usr/bin/env -S bash -o errexit -o nounset -o errtrace -o pipefail -O inherit_errexit -O nullglob -O extglob
#
# Demonstration of manual drawing like fzf.
log(){
    printf "%s\n" "$*" >> ~/.log.txt
}
source ~/.philconfig/shell_lib/bash_debug.sh
debug -f
choice=""
run(){
    # stty -echo
    local colors=("$@")
    save-curpos
    local margin=${col}
    space "$((${#colors[@]}+2))"
    save-curpos
    col=${margin}
    csi 1B
    csi "?25l"
    local selected=0
    square colors ${selected}
    while IFS='' read -n 1 key ; do
        clear_info ${#colors[@]}
        # I think this can only happen when the pressed key is ENTER
        if (( ${#key} == 0 )) ; then
            log EXITTING zero length key
            clear_square ${#colors[@]}
            choice=${colors[${selected}]}
            return
        fi
        case $key in
            's') square colors ${selected} ;;
            'c') clear_square ${#colors[@]} ;;
            'j'|$'\016'|$'\t') selected=$(( (selected+1)%${#colors[@]}))
                 square colors ${selected}
                 ;;
            'k'|$'\020') selected=$(( (selected-1)%${#colors[@]}))
                 square colors ${selected}
                 ;;
            *) info ${#colors[@]} "Key pressed: $(printf "%q, %d" "$key" "${#key}")" ;;
        esac
    done
}
info(){
    csi $(($1))B
    printf "INFO: %s" "$2" >&2
    csi $(($1))A
    csi G
}
clear_info(){
    csi $(($1))B
    csi 2K
    csi $(($1))A
    csi G
}



save-curpos(){
    local s
    csi "6n"
    read -s -d R s
    s=${s#*[}
    row=${s%;*}
    col=${s#*;}
}
restore-curpos(){
    csi "${row};${col}H"
}
csi(){
    printf "\033[%s" "$1" >&2
}
nl(){
    printf "\n" >&2
}

space(){
    local -i n=$1
    for (( i=0; i<$n; i++)) ; do
        csi "G"
        nl
    done
    csi "${n}A"
}


square(){
    local -n choices=$1
    local -i selected=${2:-0}
    local nb_choices=${#choices[@]}
    space ${nb_choices}
    local -i w=0
    for x in "${choices[@]}" ; do
        if (( ${#x} > $w )) ; then
            w=${#x}
        fi
    done
    for((i=0;i<${nb_choices};i++)) ; do
        csi 2K
        csi G
        # csi 0m ; printf "%${margin}s" " " ; 
        csi ${margin}C
        csi 46m
        csi 1
        if (( i == selected )) ; then
            csi 92m ; printf "$i:%${w}s  " "${choices[i]}" >&2 ; csi 0m
        else
            csi 93m ; printf "$i:%${w}s  " "${choices[i]}" >&2 ; csi 0m
        fi
        csi B
    done
    csi ${nb_choices}A
    csi G
}

clear_square(){
    local -i nb_choices=$1
    for ((i=0; i<${nb_choices}; i++)) ; do
        csi 2K ; csi B
    done
    csi "${nb_choices}"A
}

run "$@"
trap 'csi "?25h" ; restore-curpos; clear_square $# ; echo $choice' EXIT
