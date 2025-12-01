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
max_region_width=300
left_margin=9
right_margin=4
right_padding=3
bottom_margin=1
window_margin=1
color_choices_bg=237

### Internal state
selection_buffer=""
message=""

region=()
region_height=0  # Redundant but convenient
region_width=0   # Redundant but convenient

choices=()
choices_idx=()
choices_maxlen=0
choices_print_len=()
choices_noansi=()

window_start=0
selection_index=0
window_end=0
data=()
data_print_len=()
data_noansi=()
dir=""
prefix=""
file_explorer_mode=false
unansi=(-1 -1)

dbg-log(){
    printf "${FUNCNAME[1]}: %s\n" "$*" >> ~/.log.txt
}


coproc unansi { sed --unbuffered 's/\x1b\[[0-9;]*m//g' ; }

tui-selector-main(){

    exec 2>>~/.log.txt
    if [[ -n ${1:-} ]] ; then
        file_explorer_mode=true
    fi
    dir=${1:-}/
    prefix=${1:-}

    #### INIT
    shopt -s checkwinsize
    (:)
    if ${file_explorer_mode} ; then
        get_listing "${dir}/"
    else
        process_input
    fi
    set-choices ""
    selection=""
    selection_index=0
    selection="${choices[0]}"
    hide-cursor
    space $((${max_region_height}+bottom_margin))
    save-curpos # Needs to be done before set-region ## TODO: Ensure that's done more cleanly

    set-region

    trap 'selection="" ; exit 130' INT
    trap 'exit-handler' EXIT

    window_start=0
    selection_index=0
    window_end=${window_height}
    prev_window_height=${window_height}

    display-model "${window_start}" "${selection_index}" "${window_end}" "${region[@]}"
    while IFS='' read -s -N 1 key ; do
        case $key in
            $'\016') selection-down ;;
            $'\020') selection-up ;;
            $'\004') selection-down 5 ;;
            $'\025') selection-up 5 ;;
            $'\t')   selection-down ;;
            $'\022') exit 124 ;;
            $'\n') exit 0 ;;
            $'\E') read -t 0.1 -s -n 2 seq || true
                   case $seq in
                    '[A') selection-up ;;
                    '[B') selection-down ;;
                    '[Z') selection-up ;; # Shift-TAB
                    '[C') into-dir ;;
                    '[D') out-of-dir ;;
                    '') break
                   esac ;;
            # TODO: Clearing is only necessary if the region shrinks...
            $'\177') if [[ -n ${selection_buffer} ]] ; then
                        selection_buffer=${selection_buffer:0: -1}
                        # clear-region "${region[@]}"
                        set-choices "${selection_buffer}"
                     fi
                     ;;
            *) selection_buffer+="${key}" ; selection_index=0
                # TODO: Prevent flickering by doing clear-region only if the window
                # reduces in size or something or even just clear the number of lines
                # that need to be cleared: buf_cmove first line to clear; buf_clearline ; buf_cmove...; buf_send
                # or have display-model clear the part of the region that is unused.
                # clear-region "${region[@]}"
                set-choices "${selection_buffer}"
                ;;
        esac

        if (( ${#choices[@]} > 0 )) ; then
            selection=${choices[selection_index]}
        else
            selection=""
        fi
        display-model "${window_start}" "${selection_index}" "${window_end}" "${region[@]}"
        prev_window_height=${window_height}
    done
    clear-region "${region[@]}"
    restore-curpos
    show-cursor
}

selection-down(){
    selection_index=$((selection_index + ${1:-1}))
    if ((selection_index >= ${#choices[@]} )) ; then
        selection_index=$(( ${#choices[@]} - 1))
    elif ((selection_index >= window_end - window_margin && window_end < ${#choices[@]} )) ; then
        window_start=$((window_start +1))
        window_end=$((window_end +1))
    fi
    selection=${choices[selection_index]}
}
selection-up(){
    selection_index=$((selection_index - ${1:-1}))
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
    choices_idx=()
    choices_print_len=()
    choices_noansi=()
    for((i=0;i<${#data[@]};i++)) ; do
        if [[ ${data[i]} == *${match_str}* ]] ; then
            choices+=("${data[i]}")
            choices_noansi+=("${data_noansi[i]}")
            choices_idx+=($i)
            choices_print_len+=(${data_print_len[i]})
        fi
    done
    if (( ${#choices[@]} > 0 )) ; then
        choices_maxlen=$(max_len_by_ref choices_noansi)
    fi
    window_start=0
    window_end=$(min $((max_region_height)) $((LINES-bottom_margin)) $((${#choices[@]})))
}

process_input(){
    readarray -t data
    # After having processed data, start reading from the keyboard
    exec 0</dev/tty
    local i=0
    for d in "${data[@]}" ; do
        echo "$d" >&${unansi[1]}
        read -u ${unansi[0]} d
        data_noansi[i]="${d}"
        data_print_len[i++]=${#d}
    done
}

get_listing(){
    readarray -t data < <(ls --color=always -lth ${dir} | tail -n +2 | sed 's/\x1b\[0m\(\x1b\[K\)\?/\x1b[39;22m/g')
    local i=0
    data_print_len=()
    data_noansi=()
    for d in "${data[@]}" ; do
        echo "$d" >&${unansi[1]}
        read -u ${unansi[0]} d
        data_noansi[i]="${d}"
        data_print_len[i++]=${#d}
    done
}

dir-is-empty(){
    s=$(find "${1}" -mindepth 1 -maxdepth 1 -print -quit)
    (( ${#s} == 0 ))
}

into-dir(){
    dbg-log "selection = ${selection}"
    read _ _ _ _ _ _ _ _ filename _ <<<${choices_noansi[selection_index]}
    dbg-log "filename = ${filename}"
    dbg-log "dir = ${dir}"
    dbg-log "${prefix}/${filename}"
    if [[ -d ${prefix}/${filename} ]] ; then
        if dir-is-empty ${prefix}/${filename} ; then
            dbg-log "Not entering empty directory"
            message="Dir ${prefix}/${filename} is empty"
            return 0;
        fi
        dir=${prefix}/${filename}/
        prefix=${dir}/
        selection_buffer=""
        get_listing
        set-choices ""
        selection=${choices[0]}
        selection_index=0
    else
        message="${prefix}/${filename} is not a directory"
    fi
    clear-region "${region[@]}"
}
out-of-dir(){
    dbg-log "selection = ${selection}"
    dbg-log "dir = ${dir}"
    dir=$(dirname ${dir})/
    prefix=${dir}/
    selection_buffer=""
    get_listing
    set-choices ""
    selection=${choices[0]:-""}
    selection_index=0
    clear-region "${region[@]}"
}

max_width=3

set-region(){
    # The 12 supposes that we have less than 999 items or less because it
    # includes the width of a 3 digit number
    max_width=$(( 12 + choices_maxlen + 1))
    local x0=${left_margin}
    local x1=$(min $((x0+max_region_width)) $((COLUMNS-right_margin)) $((x0+max_width)) )
    local y0=${saved_row}
    local y1=$(min $((y0+max_region_height+1)) $((LINES-bottom_margin+1)) $((y0+${#choices[@]}+1)) )
    region=($x0 $y0 $x1 $y1)
    region_width=$((x1 - x0))
    region_height=max_region_height
    window_height=$((y1-y0-1))
}

# Display a window of items from choices/choices_desc in the screen region
# given by corners (x0,y0), (x1,y1)
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

    width=$(min $((COLUMNS-x0-right_margin)) $((choices_maxlen + 11)))
    dbg-log "choices_maxlen=${choices_maxlen}"
    buf_clear
    buf_cmove $x0 $y0
    buf_clearline
    buf_printf "Selection: \033[1;37m%s \033[0m| max_width=%d, x1-x0=%d, choices_maxlen+11=%d, width=%d, message: %s" "${selection_buffer}" "${max_width}" "$((x1-x0))" "$((choices_maxlen + 11))" "${width}" "${message}"
    message=""
    if ((${#choices[@]} == 0 )) ; then
        buf_cmove $x0 $((y0+1))
        buf_clearline
        buf_printf "[No matches]"
        j=$((j+1))
    else
        local j_start=$(( (start*window_height)/${#choices[@]}))
        local j_end=$(( j_start + (window_height*window_height)/${#choices[@]} + 1))
        for((i=${start}; i<end; i++)) do
            buf_cmove $x0 $((y0+j+1))
            local marker=" "
            local color="48;5;${color_choices_bg}"
            local scrollbar=$'\033[48;5;234m\u2592'
            if (( j_start <= j)) && ((j < j_end)) ; then
                scrollbar=$'\033[48;5;234m\u2593\033[0m'
            fi
            local text
            if ((i == selected )) ; then
                marker=">"
                color="45;36"
                printf "choices[$i]: %q\n" "${choices[i]}" >&2
            fi
            # printf "%q\n" "${c}" >> ~/.log.txt
            # TODO: Print the first ${#selection_buffer} characters in bold
            #       and the rest in normal font
            local ansi=0
            printf -v text "%s %3d/${#choices[@]}: %s" "${marker}" "$((i+1))" "${choices[i]}"
            if ((i==selected)) ; then
                printf "text: %q\n" "${text}" >&2
            fi
            local text_width=${#text}
            local ansi_compensation=$((${#choices[i]}-choices_print_len[i] + 1 ))
            local padding=$((width - (text_width - ansi_compensation) ))
            local clip_width=$((width+ansi_compensation))
            buf_clearline
            buf_printf "${scrollbar}\033[%sm%s\033[%sm%-${padding}s\033[0m" "${color}" "${text:0:${clip_width}}" "${color}" " "
            j=$((j+1))
        done
    fi
    dbg-log "region_height=${region_height}, j=${j}, i=${i}"

    # TODO: THe +3 here is because something doesn't get updated when we start
    # with a directory that has less items than the region height to one that
    # has more than the region height (or something).
    # OK: I get it.  I do 'space max_region_height' but set-region sets the
    # size of the region to a value that depends on the number of choices.
    #
    # It should have height = max_region_height
    for((; j<region_height ; j++)); do
        buf_cmove $x0 $((y0+j+1))
        buf_clearline
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
buf_send() { printf "%s" "${_buf}" >/dev/tty ; }

hide-cursor(){ printf "\033[?25l" >/dev/tty ; }
show-cursor(){ printf "\033[?25h" >/dev/tty ; }

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
    printf "\033[6n" >/dev/tty
    read -s -d R s
    s=${s#*'['} # quoting '[' not necessary but helps vim syntax highligting not get confused
    saved_row=${s%;*}
    saved_col=${s#*;}
}

message(){
    local text
    buf_clear
    buf_cmove ${message_area[1]} ${message_area[0]}
    printf -v text "%s" "${text}"
    text_
    buf_printf "%s"
}

restore-curpos(){
    printf "\033[%d;%dH" "${saved_row}" "${saved_col}" >/dev/tty
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
output-selected-filename(){
    dbg-log "BINGBONG"
    dbg-log "selection = '${selection}', selection_index=${selection_index}"
    dbg-log "$(declare -p choices)"
    read _ _ _ _ _ _ _ _ filename _ <<<${choices_noansi[selection_index]}
    dbg-log "bash_normpath: $(bash_normpath ${prefix}/${filename})"
    python3 -c "import os; print(os.path.normpath('${prefix}/${filename}'))"
}
exit-handler(){
    clear-region "${region[@]}"
    restore-curpos
    show-cursor
    dbg-log "dir = '${dir}'"
    if [[ -n ${dir} ]] ; then
        output-selected-filename
    elif [[ -n ${selection} ]] ; then
        echo "$selection"
    fi
}

# Adapted from the python code os.path.normpath
bash_normpath(){
    local start_sep
    case "${1}" in
        ///*) start_sep='/' ;;
        //*)  start_sep='//' ;;
        /*)   start_sep='/' ;;
    esac

    local IFS='/'
    local new_tokens=()
    local i=0

    for tok in ${1} ; do
        if [[ "${tok}" == '.' ]] || [[ "${tok}" == "" ]] ; then
            continue
        fi
        if [[ "${tok}" != '..' ]] \
            || ( [[ -z "${start_sep}" ]] && (( i == 0 )) ) \
            || ( (( ${#new_tokens[@]} >= 1)) \
                 && [[ ${new_tokens[i-1]} == '..' ]] ) ; then
            new_tokens[i++]=${tok}
        elif (( i >= 1 )) ; then
            ((i--))
            unset new_tokens[i]
        fi
    done
    # Note this works because IFS='/'.  the ${arr[*]} joins
    # the elements of the array 'arr' using the first char of IFS.
    final="${start_sep:-}${new_tokens[*]}"
    printf "${final:-.}\n"
}

if ! (return 0 2>/dev/null) ; then
    tui-selector-main "$@"
fi
