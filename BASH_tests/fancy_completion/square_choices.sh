#!/usr/bin/env -S bash -o errexit -o nounset -o errtrace -o pipefail -O inherit_errexit -O nullglob -O extglob
#
# Demonstration of manual drawing like fzf.
#
# NOTE: Everything is printed to STDERR except the final choice so that
# this can be used with `choice=$(this-file ${choices})`
#
# TODO: Handle window size
# A) Bail if there are more choices that we can display
#    The completion function can do something like
#    `if ! result=$(square_choices ...) ; then COMPREPLY=($(compgen -W "${choices}" -- ${cur})) ; fi
# B) Make a scrollable thing that fits in the window
log(){
    printf "%s\n" "$*" >> ~/.log.txt
}

source ~/.philconfig/shell_lib/bash_debug.sh
debug -f
choice=""
run(){
    trap 'csi "?25h" ; restore-curpos; clear_square $# ; echo $choice' EXIT
    local choices=("$@")
    save-curpos
    local margin=${col}
    space "$((${#choices[@]}+2))"
    save-curpos
    col=${margin}
    csi 1B
    csi "?25l"
    local selected=0
    _square choices ${selected}
    while IFS='' read -n 1 key ; do
        clear_info ${#choices[@]}
        # I think this can only happen when the pressed key is ENTER
        if (( ${#key} == 0 )) ; then
            # log EXITTING zero length key
            clear_square ${#choices[@]}
            choice=${choices[${selected}]}
            return
        fi
        # TODO: Could be optimized
        # TODO: Look at how Dave from YSAP reads single keys.  He handles
        # up/down arrows I'm kind of doing it but the way I'm doing it doesn't
        # distinguish between the key 'A' and the sequence for up arrow which
        # contains an A
        # TODO: When we get to scrolling
        #       - _square choices ${selected} ${first} ${last}
        #          - Display subset from first to last with this one selected
        #          - When scrolling down, change selected but if selected gets
        #            too close to last, then change last so we always see one
        #            choice past selected
        #          - Same thing for first
        # TODO: Instead of always displaying the whole square, we can have some
        #       kind of simple update function for when there is no scrolling
        #       which just redraws the previously selected item in non-selected
        #       colors and redraws the newly selected item in selected colors.
        case $key in
            's') _square choices ${selected} ;;
            'c') clear_square ${#choices[@]} ;;
            'j'|$'\016'|$'\t'|'B') selected=$(( (selected+1)%${#choices[@]}))
                 _square choices ${selected}
                 ;;
            'k'|$'\020'|'A') selected=$(( (selected+${#choices[@]}-1)%${#choices[@]}))
                 _square choices ${selected}
                 ;;
            *) info ${#choices[@]} "Key pressed: $(printf "%q, %d" "$key" "${#key}")" ;;
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
    # TODO: As YSAP showed, we can save-restore the cursor without memorizing
    # its position so maybe we don't need this.
    local s
    csi "6n"
    read -s -d R s
    s=${s#*'['} # the '[' doesn't need to be quoted but if it
                # isn't Vim's syntax highlighting gets confused.
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

_square(){
    local -i selected=${2:-0}
    local nb_choices=${#choices[@]}
    space ${nb_choices}
    # Get the max width of the candidates
    # TODO: We could do this only once instead of doing it every time we redraw
    local -i w=0
    for x in "${choices[@]}" ; do
        if (( ${#x} > $w )) ; then
            w=${#x}
        fi
    done
    local out=""
    local l=""
    for((i=0;i<${nb_choices};i++)) ; do
        # csi 2K
        # csi G
        # # csi 0m ; printf "%${margin}s" " " ; 
        # csi ${margin}C
        # csi 46m
        # csi 1
        # Format string %-3d helps ensure a nice rectangle, but of course if
        # TODO: We could also condense the output so we don't have to call
        # printf as many times.  It's a builtin so it shouldn't make too much
        # of a difference but still
        if (( i == selected )) ; then
            printf -v l "\033[2K\033[G\033[${margin}C\033[46m\033[1\033[92m %3d: %-${w}s  \033[0m\033[B" "${i}" "${choices[i]}" >&2
        else
            printf -v l "\033[2K\033[G\033[${margin}C\033[46m\033[1\033[93m %3d: %-${w}s  \033[0m\033[B" "${i}" "${choices[i]}" >&2
        fi
        out+="${l}"
        # csi B
    done
    printf "%s" "${out}" >&2
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
