#!/usr/bin/env bash

#
# This is a drop-in substitute for the `_tilde` function provided by
# bash-completion.  Like the original it
# - Takes the thing to complete as an argument and does not look at $cur or
#   ${COMP_WORDS[COMP_CWORD]}
# - Returns 1 if there are completions and zero if there are none.  Callers
#   use this by doing `_tilde ${cur} || return` so 1 means completion should
#   not continue because `_tilde` found something.
#
# But unlike the original, it
# - Filters out fake users
# - Adds Full names in parentheses with vertical alignment
#
_tilde(){
    local result=0
    if [[ ${1-} != \~* || $1 == */* ]]; then
        return 0
    fi

    #
    # Create parallel arrays of users and full names while also finding the
    # longest user and eliminating "deactivated" users.
    #
    local max_user=0 users=() fullnames=() user name home shell
    while IFS=: read user _ _ _ name home shell ; do
        if [[ "~${user}" != ${1}* ]] ; then
            continue
        fi
        if [[ ${shell} == /bin/false ]] ; then
            continue
        fi
        if ((${#user} > max_user)) ; then
            max_user=${#user}
        fi
        users+=("$user")
        fullnames+=("$name")
    done < <(getent passwd)
    max_user=$((max_user+1)) # for the `~` that we are adding back

    #
    # Inject descriptions into COMPREPLY except if there is only one result
    # (otherwise the description will also be added to the command line)
    #
    if ((${#users[@]} > 1)) ; then
        for ((i=0;i<${#users[@]};i++)) ; do
            local comp
            printf -v comp "%-${max_user}s (%s)" "~${users[i]}" "${fullnames[i]//\//-}"
            COMPREPLY+=("${comp}")
        done
    else
        for u in "${users[@]}" ; do
            COMPREPLY+=("~$u")
        done
    fi

    return $((${#COMPREPLY[@]} == 0))
}

# Could also be like this

#
# Generalize _tilde by adding a prefix option so that we can reimplement _tilde as
#
#     _tilde(){
#         if [[ ${1-} != \~* || $1 == */* ]]; then
#             return 0
#         fi
#         __usernames -p '~' ${1%\}
#     }
#
__usernames(){
    local OPTIND=1
    local prefix=''
    while getopts "p:" opt ; do
        case $opt in
            p) prefix=$OPTARG
        esac
    done
    shift $((OPTIND-1))

    local partial=$1

    #
    # Create parallel arrays of users and full names while also finding the
    # longest user and eliminating "deactivated" users.
    #
    local max_user=0 users=() fullnames=() user name home shell
    while IFS=: read user _ _ _ name home shell ; do
        if [[ "${user}" != ${partial}* ]] ; then
            continue
        fi
        if [[ ${shell} == /bin/false ]] ; then
            continue
        fi
        if ((${#user} > max_user)) ; then
            max_user=${#user}
        fi
        users+=("$prefix$user")
        fullnames+=("$name")
    done < <(getent passwd)
    max_user=$((max_user+${#prefix}))

    #
    # Inject descriptions into COMPREPLY except if there is only one result
    # (otherwise the description will also be added to the command line)
    #
    if ((${#users[@]} > 1)) ; then
        for ((i=0;i<${#users[@]};i++)) ; do
            local comp
            printf -v comp "%-${max_user}s (%s)" "${users[i]}" "${fullnames[i]//\//-}"
            COMPREPLY+=("${comp}")
        done
    else
        for u in "${users[@]}" ; do
            COMPREPLY+=("$u")
        done
    fi

    return $((${#COMPREPLY[@]} == 0))
}

#
# Like `_tilde` it can't be used as a completion function directly so we can
# create a function like this that can be used with `complete -F`
#
_users(){
    __usernames "${COMP_WORDS[COMP_CWORD]}"
}


# NOTES:
# This line pads with space added on the right ('%-${n}s'):
#
#   printf -v comp "%-${max_user}s (%s)" "~${users[i]}" "${fullnames[i]//\//-}"
#
# which is what we want.  I had it on the left ('%${n}s') at the start which is
# wrong because if all candidates have a common prefix, bash will fill up to
# there on the command line.
#
# When I did fix it, I noticed that the displaying part became MUCH slower!
#
# I don't think that it's the printf commands that take more time: that's
# because in both cases, the time it takes to see the message "Display all
# 4881 possibilities? (y or n)" is about the same and we only see this message
# when the function returns.
#
# This is only apparent when we complete `cd ~[]` and as long as we have one
# letter it's not so bad. For `cd ~s[]`, there are 600+ candidates and it is
# still apparent but not enough to be annoying.
#
# Still, I find it puzzling the difference in speed: with a warmed up getent
# cache, the slow one is 14 seconds and the fast one is 1 second!
