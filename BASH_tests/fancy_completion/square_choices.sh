#!/usr/bin/env -S bash -o errexit -o nounset -o errtrace -o pipefail -O inherit_errexit -O nullglob -O extglob
#
# Demonstration of manual drawing like fzf.
#
# NOTE: Everything is printed to STDERR except the final choice so that
# this can be used with `choice=$(this-file ${choices})`
#
### Configuration
max_region_height=10
max_region_width=80
left_margin=9
right_margin=4
right_padding=3
bottom_margin=1
window_margin=1

### Internal state
region=()
region_height=0  # Redundant but convenient
region_width=0   # Redundant but convenient
model_data=()
model_desc=()
model_data_maxlen=0
model_desc_maxlen=0
window_start=0
selection_index=0
window_end=0

main(){
    shopt -s checkwinsize
    (:)

    process_input
    space $((${max_region_height}+bottom_margin))
    set-region

    hide-cursor

    selection=""
    trap 'selection="" ; exit 130' INT
    trap 'clear-region "${region[@]}" ; restore-curpos; show-cursor; if [[ -n ${selection} ]] ; then echo "$selection" ; fi' EXIT

    window_start=0
    selection_index=0
    window_end=${region_height}

    display-model "${window_start}" "${selection}" "${window_end}" "${region[@]}"
    while IFS='' read -s -n 1 key ; do
        if (( ${#key} == 0 )) ; then
            break
        fi
        case $key in
            j) selection-down ;;
            k) selection-up ;;
        esac
        display-model "${window_start}" "${selection_index}" "${window_end}" "${region[@]}"
    done
    clear-region "${region[@]}"
    restore-curpos
    show-cursor
}

selection-down(){
    selection_index=$((selection_index + 1))
    if ((selection_index >= ${#model_data[@]} )) ; then
        selection_index=0
        window_start=0
        window_end=$((region_height))
    elif ((selection_index >= window_end - window_margin && window_end < ${#model_data[@]} )) ; then
        window_start=$((window_start +1))
        window_end=$((window_end +1))
    fi
    selection=${model_data[selection_index]}
}
selection-up(){
    selection_index=$((selection_index - 1))
    if (( selection_index < 0 )) ; then
        window_end=${#model_data[@]}
        selection_index=$((window_end - 1))
        window_start=$((window_end - region_height))
    elif (( selection_index < window_start + window_margin && window_start > 0)) ; then
        window_start=$((window_start -1))
        window_end=$((window_end -1))
    fi
    selection=${model_data[selection_index]}
}

process_input(){
    while read datum desc ; do
        model_data+=("${datum}")
        model_desc+=("${desc}")
    done
    model_data_maxlen=$(max_len_by_ref model_data)
    model_desc_maxlen=$(max_len_by_ref model_desc)
    # After having processed data, start reading from the keyboard
    exec 0</dev/tty
}

set-region(){
    save-curpos
    # The 12 supposes that we have less than 999 items or less
    local max_width=$(( 12 + $(max_len_by_ref model_data) + 1 +  $(max_len_by_ref model_desc)))
    local x0=${left_margin}
    local x1=$(min $((x0+max_region_width)) $((COLUMNS-right_margin)) $((x0+max_width)) )
    local y0=${saved_row}
    local y1=$(min $((y0+max_region_height)) $((LINES-bottom_margin)) $((y0+${#model_data[@]})) )
    region=($x0 $y0 $x1 $y1)
    region_width=$((x1 - x0))
    region_height=$((y1 - y0))
}


display-model(){
    local start=${1}
    local selected=${2}
    local end=${3}
    local x0=${4}
    local y0=${5}
    local x1=${6}
    local y1=${7}
    local width=$((x1-x0))
    local j=0
    local i

    buf_clear
    local j_start=$(( (start*region_height)/${#model_data[@]}))
    local j_end=$(( j_start + (${#model_data[@]}/region_height - 1)))
    for((i=${start}; i<end; i++)) do
        buf_cmove $x0 $((y0+j))
        local marker=" "
        local color="48;5;246;30"
        local scrollbar=$'\033[48;5;234m \033[0m'
        if (( j_start <= j)) && ((j < j_end)) ; then
            scrollbar=$'\033[48;5;252m \033[0m'
        fi
        local text
        if ((i == selected )) ; then
            marker=">"
            color="45;36"
        fi
        printf -v text "%s %3d/${#model_data[@]}: %${model_data_maxlen}s %s" \
            "${marker}" "${i}" "${model_data[i]}" "${model_desc[i]}"
        buf_printf "\033[2K${scrollbar}\033[%sm%-${width}s\033[0m" "${color}" "${text:0:${width}}"
        j=$((j+1))
    done
    buf_send
}


# It is important to IO in the biggest chunks possible to avoid any flickering
# so accumulating a bunch of text and ANSI sequences in a buffer and then
# sending it out all at once makes a HUGE difference
buf_cmove(){ _buf+=$'\033'"[${2:-};${1}H" ; }
buf_clear(){ _buf="" ; }
buf_clearline(){ _buf+=$'\033[2K' ; }
buf_printf(){
    local s=""
    printf -v s "$@"
    _buf+="$s"
}
buf_send() { printf "%s" "${_buf}" >&2 ; }

hide-cursor(){ printf "\033[?25l" >&2 ; }
show-cursor(){ printf "\033[?25h" >&2 ; }

max(){
    local m=$1
    for x in "${@:1}" ; do
        if (( x > m )) ; then m=${x} ; fi
    done
    echo $m
}
min(){
    local m=$1
    for x in "${@:1}" ; do
        if (( x < m )) ; then m=${x} ; fi
    done
    echo $m
}
max_len_by_ref(){
    local -n _ref=$1
    local max_len=${#_ref[1]}
    for e in "${_ref[@]:1}" ; do
        if (( ${#e} > max_len )) ; then
            max_len=${#e}
        fi
    done
    echo ${max_len}
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


save-curpos(){
    # TODO: As YSAP showed, we can save-restore the cursor without memorizing
    # its position so maybe we don't need this.
    local s
    printf "\033[6n" >&2
    read -s -d R s
    s=${s#*'['} # quoting '[' not necessary but helps vim syntax highligting not get confused
    saved_row=${s%;*}
    saved_col=${s#*;}
}

restore-curpos(){
    printf "\033[%d;%dH" "${saved_row}" "${saved_col}" >&2
}

# Print a N newlines then move the cursor up by N positions.  This ensures that
# we have enough space to draw our box while also possibly causing the current
# output to scroll up.
space(){
    buf_clear
    local -i n=$1
    for (( i=0; i<$n; i++)) ; do
        buf_printf "\033[G\n"
    done
    buf_printf "\033[${n}A"
    buf_send
}

if ! (return 0 2>/dev/null) ; then
    main "$@"
fi
