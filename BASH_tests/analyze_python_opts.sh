#!/bin/bash
#
# This is probably the dumbest way to spend a couple hours but there you go,
# parse arguments to python3 to check if python3 was called with the -i with
# either a file or -c "some code" or -c"some code".
#
# In that case, it doesn't read the ~/.pyrc file so I wouldn't get my cool
# yellow and blue prompts.
#
# The first half splitting the arguments between arguments for python and
# arguments for the file or the code (-c).
#
# Once the splitting is done, we can use getopt to reliably determine if:w
#


# Just parsing the upcoming code is causes a syntax error if extglob is not
# activated.  We save its value, activate it, then set it back after having
# read this function's definition.
# The function itself executes in a subshell so it doesn't need to do the
# save-set-reset thing, it just sets extglob.
_extglob=$(shopt -p extglob)
shopt -s extglob
function python3(){(
    shopt -s extglob
    printf "$(shopt -s extdebug; declare -F python3): EXPERIMENTAL\n" >&2
    local py_args=()
    local script_args=()
    local file=""
    local code=""
    local i=1
    #
    # Accumulate all command line arguments until -c or a file
    # into py_args, when -c"...", of -c "..." is found, define code to be
    # the "...". When a *.py file is found define file.
    #
    for ((i=1;i<=$#;i++)) ; do
        # https://stackoverflow.com/a/4555979/5795941
        # Requires 'shopt -s extglob'
        # It looks like the case '-*([^c])c' could include the '-c' case
        # but if the '-c*([^c])c' handled '-c', it would put '-' in py_args.
        # So in fact we need a case '-c' and a case '-+([^c])c'.  Same for
        # the '-c*' and '-+([^c])c*' cases, they cannot be treated the same
        # way.
        case ${!i} in
            -c) # ex: python3 -c "print('allo')"
                local x=$((i+1))
                code="${!x}"
                i=$((i+2))
                break
                ;;
            -c*) # ex: python3 -c"print('allo')"
                code="${!i#-c}"
                i=$((i+1))
                break
                ;;
            -+([^c])c) # ex: python3 -ic "print('allo')"
                py_args+=("$(echo "${!i}" | sed 's/c.*$//')")
                local x=$((i+1))
                code="${!x}"
                i=$((i+2))
                break;
                ;;
            -+([^c])c*) # ex: python3 -ic"print('allo')"
                py_args+=("$(echo "${!i}" | head -n 1 | sed 's/c.*$//')")
                code="$(echo "${!i}" | head -n 1 | sed 's/^-[^c]*c//')"
                if [[ "${!i}" == *$'\n'* ]] ; then
                    code+=$'\n'
                    code+="$(echo "${!i}" | tail -n +2)"
                fi
                i=$((i+1))
                break;
                ;;
            *.py)
                file="${!i}"
                i=$((i+1))
                break
                ;;
            *) py_args+=("${!i}") ;;
        esac
    done

    #
    # Accumulate all args after -c"...", -c "..., or a file into
    # the array script_args
    #
    for ((;i<=$#;i++)) ; do
        script_args+=("${!i}")
    done

    #
    # Use getopt to determine reliably if -i is present in py_args
    #
    local spec=Bbc:dEhiIm:O::qsSuvVW:X:x
    local interactive=0
    eval local normalized_args=($(getopt -n "" -o ${spec} -- "${py_args[@]}"))
    for a in "${normalized_args[@]}" ; do
        if [[ "${a}" == "-i" ]] ; then
            interactive=1
            break;
        fi
    done

    #
    # If non-interactive or there is no -c CODE or file in the command line,
    # just run the python3 command with forwarded args
    #
    if [[ "${interactive}" == 0 ]] || ([[ -z "${code}" ]] && [[ -z "${file}" ]]) ; then
        command python3 "$@"
        return
    fi

    #
    # Adapt code or file by prepending ~/.pyrc.  For files, the command is
    # changed to a python -c CODE with CODE containing ~/.pyrc, some other
    # hacks and finally the content of the file
    #
    local wc="$(wc -l ~/.pyrc)"
    local pyrc_nlines=${wc% *}
    local new_code
    if [[ "${code}" != "" ]] ; then
        new_code="$(cat ~/.pyrc)"$'\n'"${code}"
        offset=${pyrc_nlines}
    elif [[ "${file}" != "" ]] ; then
        new_code="$(cat ~/.pyrc)"$'\n'
        new_code+="import sys"$'\n'
        new_code+="__file__='${file}'"$'\n'
        new_code+="sys.argv[0]=\"${file}\""$'\n'
        new_code+="$(cat "${file}")"
        offset=$((pyrc_nlines + 3))
    fi

    #
    # Run the same python command with code stderr optionally redirected through
    # a filter that will modify line numbers in traceback lines referring to
    # code from -c or a file so that they match the original argument to -c or
    # the original file.
    #
    # This doesn't work because since the first python3's output is not a tty,
    # it is line bufferred.
    #
    if [[ -v PYRC_NOFILTER ]] ; then
        command python3 -u "${py_args[@]}" -c "${new_code}" "${script_args[@]}"
    else
        PHIL_SUPER_UNBUFFERED=y ~/fs1/bin/python3 -u "${py_args[@]}" -c "${new_code}" "${script_args[@]}" &> >(PHIL_SUPER_UNBUFFERED=y command ~/fs1/bin/python3 -u -c "
import sys
import signal
signal.signal(signal.SIGINT, signal.SIG_IGN)

while True:
    c = sys.stdin.read(1)
    if not c:
        break
    if ord(c) != 1:
        # print(f'normal: c={c}')
        l=c
        l += sys.stdin.readline()
        if l.startswith('  File \"<string>\"'):
            print(f'  >>> original line: \"{l[:-1]}\"')
            parts = l.split(',')
            if sys.argv[1]:
                print(parts[0].replace('<string>',sys.argv[1])+', ', end='')
            else:
                print(parts[0]+', ', end='')
            line_parts=parts[1].split(' ')
            print(line_parts[1] + ' ', end='')
            # print(f'line_parts={line_parts}')
            print(int(line_parts[2]) - ${offset}, end='')
            print(',', end='')
            if len(parts) == 3:
                print(parts[2], end='')
            else:
                print()
        else:
            print(l, end='')
    else:
        # print(f'start_prompt: c={c}')
        print(c, end='')
        while True:
            c = sys.stdin.read(1)
            print(c, end='')
            if not c or ord(c) == ' ':
                break
" "${file}")
    fi
)}
${_extglob}
