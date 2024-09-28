#
# This test demonstrates a syntax that allows using variables on the left
# hand side of a redirection operator.
#
################################################################################
# Open file 'fd_8' with file descriptor 8
################################################################################
base_syntax(){
    printf "==== ${FUNCNAME[0]} ...\n"
    exec 15>fd_15
    echo "HELLO 15" >&15
}

################################################################################
# Attempt to redirect but it doesn't work.  This gives
#   fd_variable.sh: line _: exec: 16: not found
# but we just saw above that
#   exec 8>fd_8
# works.  So what's wrong here?
################################################################################
syntax_that_doesnt_work(){
    printf "==== ${FUNCNAME[0]} ...\n"

    local fd=16
    exec ${fd}>fd_${fd} # ERROR HERE

    echo "HELLO ${fd}" >&${fd}
}
################################################################################
# Seeing that
#   exec 8>...
# worked but
#   exec ${fd}>...
# doesn't we try this and it works
################################################################################
syntax_that_works_with_eval(){
    printf "==== ${FUNCNAME[0]} ...\n"

    local fd=17
    eval "exec ${fd}>fd_${fd}"

    echo "fd=${fd}"
    echo "HELLO ${fd}" >&${fd}
}

################################################################################
# On this stack overflow answer https://unix.stackexchange.com/a/669677/161630
# I noticed that he used this syntax.  With this syntax bash will find a
# file descriptor and *write* it in the variable.
# NOTE: When used to close a file descriptor, this same syntax ({varname}>&-, or
# {varname}<&-) will *read* the value of the variable and close that fd.
################################################################################
special_syntax(){
    printf "==== ${FUNCNAME[0]} ...\n"

    exec {fd}>fd_${fd}

    echo "fd=${fd}"
    echo "HELLO ${fd}" >&${fd}
}

################################################################################
# When used to redirect the output of a single command instead of using exec,
# the redirection persists.
# Note: writing to a file descriptor is not like redirecting to a file.  This
# can be confusing because `>>file` and `>file` open a file in append and write
# mode respectively.
#
# The commands
#   echo "a" >file    # opens in write mode, write "a\n" to the fd1, close fd1
#   echo "b" >>file   # opens in append mode, write "b\n" to the fd2, close fd2
#   echo "c" >>file   # opens in append mode, write "c\n" to the fd3, close fd3
# and
#   exec {fd}>file    # open fd1 in write mode
#   echo "a" >&${fd}  # write "a\n" to fd1
#   echo "b" >&${fd}  # write "b\n" to fd1
#   echo "c" >&${fd}  # write "c\n" to fd1
#   exec {fd}>&-      # close fd1
# both end up with the same file.  There is no >>&${fd}.  You don't append to
# a file descriptor, you write to it.  The >> vs > is about how the file was
# opened and decides whether we clear its content on opening or not.
################################################################################
stay_open(){
    printf "==== ${FUNCNAME[0]} ...\n"
    echo "Apple" {my_fd}>stay_open >&${my_fd}
    echo "Apricot" >&${my_fd}
    echo "Banana"  >&${my_fd}
    echo "Cherry"  >&${my_fd}
    exec {my_fd}>&- # Close the file
    echo "my_fd=${my_fd}"
}

################################################################################
#
################################################################################
reading(){
    printf "==== ${FUNCNAME[0]} ...\n"
    exec {read_fd}<stay_open
    <&${read_fd} read one_line
    echo "one_line = ${one_line}"
    <&${read_fd} read one_line
    echo "one_line = ${one_line}"
    <&${read_fd} read one_line
    echo "one_line = ${one_line}"
    <&${read_fd} read one_line
    echo "one_line = ${one_line}"
}

base_syntax
syntax_that_works_with_eval
special_syntax
stay_open
reading
# This function stops the program even if I don't have `set -e`
# so run it last
syntax_that_doesnt_work
