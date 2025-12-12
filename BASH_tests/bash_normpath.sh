#!/bin/bash
# BASH implementation of python's os.path.normpath function.
# Run 'python3 -c "import os; print(os.path.normpath.__code__.co_filename)"'
# to get the file for the reference implementation.
# As shown below, this has been tested to produce the exact same output
# for a variety of edge cases.  The main difficulty is deciding what to do
# with '..' when there is nothing for it to cancel out.
# ../A -> ../A but A/../B -> B
bash-normpath(){
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
            # See nullglob.bash for why there are quotes here
            unset 'new_tokens[i]'
        fi
    done
    # Note this works because IFS='/'.  the ${arr[*]} joins
    # the elements of the array 'arr' using the first char of IFS.
    final="${start_sep}${new_tokens[*]}"
    printf "${final:-.}\n"
}

# Easier to understand implementation
bash-normpath(){
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
        # Skip 'dot's and empty path components from consecutive slashes
        if [[ "${tok}" == '.' ]] || [[ "${tok}" == "" ]] ; then
            continue
        fi

        # The usual: '..' cancels out a previous token unless
        # that previous token is also '..'
        if [[ "${tok}" == '..' ]] && (( i > 0 )) && [[ ${new_tokens[i-1]} != .. ]] ; then
            unset 'new_tokens[--i]'
            continue
        fi

        # For absolute paths, we don't allow '..'s after the first slash
        if [[ "${tok}" == '..' ]] && (( i == 0 )) && [[ -n ${start_sep} ]] ; then
            continue
        fi

        # In every other case, we add the token which could still be '..'
        # which can't cancel out a previous non-'..' token.
        new_tokens[i++]=${tok}
    done
    final="${start_sep:-}${new_tokens[*]}"
    printf "${final:-.}\n"
}

test_expect(){
    value=$(bash-normpath "${1}")
    if assert_value_eq_expected "${value}" "${2}" ; then
        echo "SUCCESS: ${1} -> ${value}"
    fi
}

expect_fail(){
    if bash-normpath "${1}" 2>/dev/null ; then
        echo "bash_normpath '${1}' was supposed to fail but did not"
        return 1
    fi
}
assert_value_eq_expected(){
    if [[ "${1}" != "${2}" ]] ; then
        echo "Assertion failed: value:'${1}' != expected:'${2}'"
        return 1
    fi
}
test_pynormpath(){
    local value=$(bash-normpath "${1}")
    local expected=$(python3 -c "import os; print(os.path.normpath('${1}'))")
    if [[ "${value}" != "${expected}" ]] ; then
        echo "value was different from expected:"
        echo " input: '${1}'"
        echo "  bash: '${value}'"
        echo "python: '${expected}'"
        return 1;
    fi
}
main(){
    test_pynormpath src/../A A
    test_pynormpath /usr/bin/../etc/ /usr/etc
    test_pynormpath //usr/bin/../etc/ /usr/etc
    test_pynormpath ////usr/bin/../etc/ /usr/etc
    test_pynormpath ///usr/bin/../etc/ /usr/etc
    test_pynormpath "" ""
    test_pynormpath / /
    test_pynormpath ./ ""
    test_pynormpath src/.. ""
    test_pynormpath src/../../A
    test_pynormpath /src/../../../
    # expect_fail src/../../A
    # expect_fail ../A
}
main "$@"
