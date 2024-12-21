#!/bin/bash
# BASH implementation of python's os.path.normpath function.
# Run 'python3 -c "import os; print(os.path.normpath.__code__.co_filename)"'
# to get the file for the reference implementation.
# As shown below, this has been tested to produce the exact same output
# for a variety of edge cases.  The main difficulty is deciding what to do
# with '..' when there is nothing for it to cancel out.
# ../A -> ../A but A/../B -> B
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
    final="${start_sep}${new_tokens[*]}"
    printf "${final:-.}\n"
}

#    for comp in comps:
#        if comp in (empty, dot):
#            continue
#        if (comp != dotdot or (not initial_slashes and not new_comps) or
#             (new_comps and new_comps[-1] == dotdot)):
#            new_comps.append(comp)
#        elif new_comps:
#            new_comps.pop()

test_expect(){
    value=$(bash_normpath "${1}")
    if assert_value_eq_expected "${value}" "${2}" ; then
        echo "SUCCESS: ${1} -> ${value}"
    fi
}

expect_fail(){
    if bash_normpath "${1}" 2>/dev/null ; then
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
    local value=$(bash_normpath "${1}")
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
    # expect_fail src/../../A
    # expect_fail ../A
}
main "$@"
