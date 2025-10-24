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

# source ~/.philconfig/shell_lib/bash_debug.sh
# debug -f
choice=""

init_display(){
    local lines=$1
    local cols=$2
    save-curpos
    space ${lines}
}

finalize_display(){
    local lines=$1
    local cols=$2
    clear_rectangle $lines $cols
    restore-curpos
}

process_input(){
    declare -ga model_data=()
    declare -ga model_desc=()
    declare -ga window=(-1 -1 -1)
    declare -g  model_data_width=0
    declare -g  model_desc_width=0
    while read datum desc ; do
        if (( ${#datum} > model_data_width )) ; then
            model_data_width=${#datum}
        fi
        if (( ${#desc} > model_desc_width )) ; then
            model_desc_width=${#desc}
        fi
        model_data+=("${datum}")
        model_desc+=("${desc}")
    done
    exec 0</dev/tty
}
source ~/.philconfig/shell_lib/functions.sh

display-model(){
    local start=${1}
    local selected=${2}
    local end=${3}
    local x0=${4:-8}
    local y0=${5:-3}
    local x1=${6}
    local y1=${7}
    local available_space=$((x1 - x0))
    buf_clear
    local j=0
    for((i=${start}; i<end; i++)) do
        buf_cmove ${x0} $((y0+j))
        local marker=" "
        local color="48;5;246;30"
        local text
        if ((i == selected )) ; then
            marker=">"
            color="45;36"
        fi
        printf -v text " %s %3d/${#model_data[@]}: %${model_data_width}s %-${model_desc_width}s" \
            "${marker}" "${i}" "${model_data[i]}" "${model_desc[i]}"
        buf_printf "\033[2K\033[%sm%-${available_space}s\033[0m" "${color}" "${text:0:available_space}"
        j=$((j+1))
    done
    buf_send
}

buf_cmove(){
    _buf+=$'\033'"[${2:-};${1}H"
}
cmove(){
    printf "\033[${2:-0};${1}H" >&2
}
buf_clear(){
    _buf=""
}
buf_send(){
    printf "%s" "${_buf}" >&2
}
buf_printf(){
    local s=""
    printf -v s "$@"
    _buf+="$s"
}
buf_clearline(){
    _buf+=$'\033[2K'
}
max(){
    m=$1
    for x in "${@:1}" ; do
        if (( x > m )) ; then m=${x} ; fi
    done
    echo $m
}
min(){
    m=$1
    for x in "${@:1}" ; do
        if (( x < m )) ; then m=${x} ; fi
    done
    echo $m
}

region=()

r(){
    ####### Acquire input
    process_input
    ####### Init display
    exec 0</dev/tty  # Important so we can get cursor position
                     # Maybe doable using the save-restore ANSI sequences directly though
    shopt -s checkwinsize
    (:)
    hide-cursor
    box_height=$(min 10 ${#model_data[@]})
    space ${box_height}
    save-curpos
    trap 'selection="" ; exit' INT
    trap 'clear-region "${region[@]}" ; restore-curpos; show-cursor; if [[ -n ${selection} ]] ; then echo "${model_data[${window[1]}]}" ; fi' EXIT
    model_desc_width=40
    window=(0 0 ${box_height})
    x0=4
    y0=${saved_row}
    x1=$(max 80 $((COLUMNS - 4)) )
    y1=$((y0 + window[2] - window[0]))
    region=($x0 $y0 $x1 $y1)
    selection=""

    display-model "${window[@]}" ${x0} ${y0} ${x1} ${y1}
    while IFS='' read -s -n 1 key ; do
        if (( ${#key} == 0 )) ; then
            break
        fi
        case $key in
            j) selection-down ;;
            k) selection-up ;;
        esac
        display-model "${window[@]}" ${x0} ${y0} ${x1} ${y1}
    done
    clear-region "${region[@]}"
    restore-curpos
    show-cursor
}
selection-down(){
    window[1]=$((window[1] + 1))
    margin=1
    if ((window[1] >= ${#model_data[@]} )) ; then
        window[1]=0
        window[0]=0
        window[2]=$((box_height))
    elif ((window[1] >= window[2] - margin && window[2] < ${#model_data[@]} )) ; then
        window[0]=$((window[0] +1))
        window[2]=$((window[2] +1))
    fi
    selection=${model_data[window[1]]}
}
selection-up(){
    window[1]=$((window[1] - 1))
    margin=1
    if (( window[1] < 0 )) ; then
        window[2]=${#model_data[@]}
        window[1]=$((window[2] - 1))
        window[0]=$((window[2] - box_height))
    elif (( window[1] < window[0] + margin && window[0] > 0)) ; then
        window[0]=$((window[0] -1))
        window[2]=$((window[2] -1))
    fi
    selection=${model_data[window[1]]}
}

hide-cursor(){
    printf "\033[?25l" >&2
}
show-cursor(){
    printf "\033[?25h" >&2
}

clear-region(){
    local x0=$1
    local y0=$2
    local x1=$3 # unused
    local y1=$4
    buf_clear
    for((y=${y0}; y<${y1} ; y++)); do
        buf_cmove ${x0} ${y}
        buf_clearline
    done
    buf_send
}

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

saved_row=1
saved_col=1


save-curpos(){
    # TODO: As YSAP showed, we can save-restore the cursor without memorizing
    # its position so maybe we don't need this.
    local s
    printf "\033[6n" >&2
    read -s -d R s
    s=${s#*'['} # the '[' doesn't need to be quoted but if it
                # isn't Vim's syntax highlighting gets confused.
    saved_row=${s%;*}
    saved_col=${s#*;}
}

restore-curpos(){
    printf "\033[%d;%dH" "${saved_row}" "${saved_col}" >&2
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

select-process(){
    ps -f -u phc001 | ( read _ ; while read u pid _ _ _ _ _ cmd ; do echo $pid $cmd ; done ) | r
}
select-job(){
    jobids=($(qselect -u $USER))
    if ((${#jobids[@]} == 0)) ; then
        return
    fi
    #text="$(echo ${jobids} | xargs qstat -w)"
    j=$(echo ${jobids} | xargs qstat -w | tail -n +2 | r)
    if [[ -n $j ]] ; then
        qdel $j
    fi
}


# run "$@"
if ! (return 0 2>/dev/null) ; then
    r "$@"
fi
