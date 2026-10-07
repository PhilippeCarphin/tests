# This code demonstrates a technique that I saw in the autocomplete for
# glab (gitlab's command line tool).
#
# The technique consists in injecting descriptions in autocomplete candidates
#
# The autocomplete for Docker has the *exact* same code but both of them show
# no attribution so I don't know where the idea actually comes from.
#
# This function is meant to be copied in other code with the '_cmd' prefix
# replaced with something else, possibly '_' and the name of the command'
#
# Note that glab and docker use a different way of getting candidates and
# their descriptions: they call an executable which produces lines containing
# a matching candidate and a description separated by a tab character.
#
# The shell code then splits these lines and formats them forming two parallel
# arrays comp and desc where ${desc[i]} is the description of ${comp[i]}.
#
# My version is different: The completion is responsible for creating an array
# of matching candidates and providing one or more associative arrays
# containing the descriptions.
#

#
# Returns an array of formatted candidate-description elements
#
# Params:
# - 1: Name of associative array mapping candidates to descriptions
# - 2: Name of array containing matching candidates, defaults to COMPREPLY
# - 3: Name of output array for formatted candidate-description elements
#      defaults to COMPREPLY
#
# Note:
# - The array of candidates must already have been filtered to contain
#   only candidates matching the value of ${cur}
# - If there is only one candidate, no description is added.
#
_cmd_add_descriptions_by_ref(){
    local -n _desc_array=$1
    local -n _comp_array=${2:-COMPREPLY}
    local -n _comp_desc=${3:-COMPREPLY}
    if ((${#_comp_array[@]} <= 1)) ; then
        _comp_desc=("${_comp_array[@]}")
        return
    fi

    #
    # Get max lengths of candidates for alignment
    #
    local max_comp=0 comp
    for comp in "${_comp_array[@]}" ; do
        if (( ${#comp} > max_comp )) ; then
            max_comp=${#comp}
        fi
    done

    #
    # Compute the space available for descriptions
    # The '-4' is the space, the two parens, and the potential '…'
    #
    local i max_desc_len=$((COLUMNS - max_comp - 4))

    #
    # If this length is too short, then there is no point in even
    # putting descriptions.  Just return an array of candidates
    # without descriptions
    #
    if (( max_desc_len < 10 )) ; then
        _comp_desc=("${comp_array[@]}")
        return
    fi

    #
    # Format completion+descriptions so that descriptions are vertically
    # aligned and do not go past the width of the screen
    #
    for((i=0;i<${#_comp_array[@]};i++)); do
        comp=${_comp_array[i]}
        local desc=${_desc_array[${comp}]}
        if ((${#desc} > max_desc_len)) ; then
            desc=${desc:0:$((max_desc_len-1))}
            desc+='…'
        fi
        printf -v _comp_desc[i] "%-${max_comp}s (%s)" "${comp}" "${desc}"
    done
}

_cmd_options=(-fruit -vegetable -meat)
declare -A _cmd_options_desc=(
    [-fruit]="Select fruit for meal"
    [-vegetable]="Select vegetable for meal"
    [-meat]="Select the meat for the meal"
)

_cmd_fruit_values=(apple apricot banana cherry)
declare -A _cmd_fruit_desc=(
    [apple]="A green or red fruit"
    [apricot]="A small yellow-orange stone fruit"
    [banana]="A long yellow fruit"
    [cherry]="A small red fruit"
)

# _cmd_vegetable_values=(carrot potato onion) # == "${!_cmd_vegetable_desc[@]}"
declare -A _cmd_vegetable_desc=(
    [carrot]="A long and orange vegetable"
    [potato]="A somewhat spherical starchy vegetable"
    [onion]="A spherical white vegetable"
)

meats=(beef buffalo chicken pork pigeon veal)
meat_desc=(
    "The flesh of a cow or bull"
    "An animal with horns"
    "A flightless bird"
    "The flesh of a pig"
    "A bird you probably don't want to eat"
    "The flesh of a baby cow"
)

_cmd(){
    local cur=${COMP_WORDS[COMP_CWORD]}
    local prev=${COMP_WORDS[COMP_CWORD-1]}
    case ${prev} in
        -fruit)
            COMPREPLY=($(compgen -W "${_cmd_fruit_values[*]}" -- "${cur}"))
            _cmd_add_descriptions _cmd_fruit_desc
            ;;
        -vegetable)
            # NOTE: We don't need the indexed array if we use the keys as
            # the potential candidates:
            COMPREPLY=($(compgen -W "${!_cmd_vegetable_desc[*]}" -- "${cur}"))
            _cmd_add_descriptions _cmd_vegetable_desc
            ;;
        -meat)
            _cmd_do_comp_desc_one_shot
            ;;
        *)
            COMPREPLY=($(compgen -W "${!_cmd_options_desc[*]}" -- "${cur}"))
            _cmd_add_descriptions _cmd_options_desc
            ;;
    esac
}

#
# An unnecessary and potentially ineffective optimization:
#
# Supposing that lookup in an associative array is slower than a lookup by
# index in an indexed array, this function does the description thing by
# using two parallel arrays where ${meat_desc[i]} is the description of
# ${meat[i]}
#
_cmd_do_comp_desc_one_shot(){
    local comp=() max_comp=0 desc=()
    for((i=0;i<${#meats[@]};i++)) ; do

        meat=${meats[i]}
        if [[ ${meat} != ${cur}* ]] ; then
            continue
        fi

        comp+=("${meat}")
        desc+=("${meat_desc[i]}")
        if (( ${#meat} > max_comp )) ; then
            max_comp=${#meat}
        fi
    done

    if (( ${#comp[@]} <= 1 )) ; then
        COMPREPLY=("${comp[@]}")
        return
    fi

    local max_desc_len=$((COLUMNS - max_comp - 4))
    local i
    for((i=0;i<${#comp[@]};i++)); do
        local c=${comp[i]}
        local d=${desc[i]}
        if ((${#d} > max_desc_len)) ; then
            d=${d:0:$((max_desc_len-1))}
            d+='…'
        fi
        printf -v COMPREPLY[i] "%-${max_comp}s (%s)" "${c}" "${d}"
    done
}

complete -F _cmd cmd
