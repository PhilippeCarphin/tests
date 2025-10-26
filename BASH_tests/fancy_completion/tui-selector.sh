#!/usr/bin/env -S bash -o errexit -o nounset -o errtrace -o pipefail -O inherit_errexit -O nullglob -O extglob
#
# Demonstration of manual drawing like fzf.
#
# NOTE: Everything is printed to STDERR except the final choice so that
# this can be used with `choice=$(this-file ${choices})`
#
# Ideas:
# - A text field gets filled and we change the display to only the things
#   that match the content of the text field.
#   -> Matches is a list of indices in the main list who match the field
#     The window becomes a window into the match list
#   -> Window becomes formed with indices in the match list instead of the
#      main list.
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
selection_buffer=""

region=()
region_height=0  # Redundant but convenient
region_width=0   # Redundant but convenient

choices=()
choices_idx=()
choices_desc=()
choices_maxlen=0
choices_desc_maxlen=0

window_start=0
selection_index=0
window_end=0
data=()
data_desc=()


set-bing-bong-matches(){
    local word=$1

}

tui-selector-main(){

    #### INIT
    shopt -s checkwinsize
    (:)
    process_input
    set-choices ""
    hide-cursor
    space $((${max_region_height}+bottom_margin))
    save-curpos # Needs to be done before set-region ## TODO: Ensure that's done more cleanly

    set-region


    selection=""
    trap 'selection="" ; exit 130' INT
    trap 'clear-region "${region[@]}" ; restore-curpos; show-cursor; if [[ -n ${selection} ]] ; then echo "$selection" ; fi' EXIT

    window_start=0
    selection_index=0
    window_end=${window_height}

    display-model "${window_start}" "${selection}" "${window_end}" "${region[@]}"
    while IFS='' read -s -n 1 key ; do
        if (( ${#key} == 0 )) ; then
            break
        fi
        case $key in
            $'\016') selection-down ;;
            $'\020') selection-up ;;
            $'\004') selection-down ; selection-down ; selection-down ; selection-down ;;
            $'\025') selection-up ; selection-up ; selection-up ; selection-up ;;
            $'\022') exit 124 ;; 
            $'\E') read -t 0.1 -s -n 2 seq || true
                   case $seq in
                    '[A') selection-up ;;
                    '[B') selection-down ;;
                    '') break
                   esac ;;
            $'\177') if [[ -n ${selection_buffer} ]] ; then selection_buffer=${selection_buffer:0: -1}  ; fi ;;
            *) selection_buffer+="${key}" ; selection_index=0 ;;
        esac

        clear-region "${region[@]}"
        set-choices "${selection_buffer}"
        set-region

        display-model "${window_start}" "${selection_index}" "${window_end}" "${region[@]}"
    done
    clear-region "${region[@]}"
    restore-curpos
    show-cursor
}

selection-down(){
    selection_index=$((selection_index + 1))
    if ((selection_index >= ${#choices[@]} )) ; then
        selection_index=$((selection_index - 1))
    elif ((selection_index >= window_end - window_margin && window_end < ${#choices[@]} )) ; then
        window_start=$((window_start +1))
        window_end=$((window_end +1))
    fi
    selection=${choices[selection_index]}
}
selection-up(){
    selection_index=$((selection_index - 1))
    if (( selection_index < 0 )) ; then
        selection_index=0
    elif (( selection_index < window_start + window_margin && window_start > 0)) ; then
        window_start=$((window_start -1))
        window_end=$((window_end -1))
    fi
    selection=${choices[selection_index]}
}

set-choices(){
    local match_str="$1"
    choices=()
    choices_desc=()
    choices_idx=()
    for((i=0;i<${#data[@]};i++)) ; do
        if [[ ${data[i]} == ${match_str}* ]] then
            choices+=("${data[i]}")
            choices_idx+=($i)
            choices_desc+=("${data_desc[i]}")
        fi
    done
    if (( ${#choices[@]} > 0 )) ; then
        choices_maxlen=$(max_len_by_ref choices)
        choices_desc_maxlen=$(max_len_by_ref choices_desc)
    fi
    window_start=0
    window_end=$(min $((max_region_height)) $((LINES-bottom_margin)) $((${#choices[@]})))
}

process_input(){
    while read datum desc ; do
        data+=("${datum}")
        data_desc+=("${desc}")
    done
    # After having processed data, start reading from the keyboard
    exec 0</dev/tty
}
max_width=3

set-region(){
    # The 12 supposes that we have less than 999 items or less
    max_width=$(( 12 + choices_maxlen + 1 +  choices_desc_maxlen + 1))
    local x0=${left_margin}
    local x1=$(min $((x0+max_region_width)) $((COLUMNS-right_margin)) $((x0+max_width)) )
    local y0=${saved_row}
    local y1=$(min $((y0+max_region_height+1)) $((LINES-bottom_margin+1)) $((y0+${#choices[@]}+1)) )
    region=($x0 $y0 $x1 $y1)
    region_width=$((x1 - x0))
    region_height=$((y1 - y0))
    window_height=$((region_height - 1))
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

    buf_cmove $x0 $y0
    buf_printf "Selection: \033[1;37m%s \033[0m| max_width=%d" "${selection_buffer}" "${max_width}"
    if ((${#choices[@]} == 0 )) ; then
        buf_cmove $x0 $((y0+1))
        buf_printf "==="
        buf_send
        return
    fi

    local j_start=$(( (start*window_height)/${#choices[@]}))
    local j_end=$(( j_start + (window_height*window_height)/${#choices[@]} + 1))
    for((i=${start}; i<end; i++)) do
        buf_cmove $x0 $((y0+j+1))
        local marker=" "
        local color="48;5;246;30"
        local scrollbar=$'\033[48;5;234m\u2592'
        if (( j_start <= j)) && ((j < j_end)) ; then
            scrollbar=$'\033[48;5;234m\u2593\033[0m'
        fi
        local text
        if ((i == selected )) ; then
            marker=">"
            color="45;36"
        fi
        # TODO: Print the first ${#selection_buffer} characters in bold
        #       and the rest in normal font
        printf -v text "%s %3d/${#choices[@]}: %${choices_maxlen}s %s" \
            "${marker}" "${i}" "${choices[i]}" "${choices_desc[i]}"
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
    local max_len=${#_ref[0]}
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
    tui-selector-main "$@"
fi
