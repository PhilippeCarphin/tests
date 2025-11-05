#!/bin/sh

#!/bin/bash

################## /usr/bin/cd ################################
# #!/bin/sh
# # $FreeBSD: src/usr.bin/alias/generic.sh,v 1.2 2005/10/24 22:32:19 cperciva Exp $
# # This file is in the public domain.
# builtin `echo ${0##*/} | tr \[:upper:] \[:lower:]` ${1+"$@"}
###############################################################

# Curious about /usr/bin/cd, I looked at the filen and was intrigued by the
# expression `${1+"$@"}` which is like doing
# if $1 is defined ; then
#     cmd "$@"
# else
#     cmd
# fi
#
# which seems unnecessary because of how quoting arrays works: with `cmd "$@"`,
# cmd gets zero arguments if $@ is "empty" but it looks to me like they are
# worried about cmd getting a single empty-string argument when $@ is empty.
#
# This test shows that this is not the case.  However, maybe it depends on the
# shell.

# Arguments with spaces stay as single arguments
# no empty-string argument for print_args if $# == 0.
echo '=== print_args.sh "$@" ==='
./print_args.sh "$@"

# Same result as above (I think the smart quotes make the ${1+ thing not useful
echo '=== print_args.sh "${1+$@}" ==='
./print_args.sh "${1+$@}"

echo '=== print_args.sh ${1+"$@"} ==='
./print_args.sh ${1+"$@"}

# Args with spaces get separated
# No empty string arg for print_args if $# == 0
echo '=== print_args.sh ${1+$*} ==='
./print_args.sh ${1+$*}

echo '=== print_args.sh $*'
./print_args.sh $*

# No in-between for '$*'.  Smart quotes only work for '$@'.
# Without quotes, '$*' splits up arguments that have spaces.
# With quotes '$*' becomes a single argument.

# Combines all arguments
# empty string argument for print_args if $# == 0.
echo '=== print_args.sh "${1+$*}" ==='
./print_args.sh "${1+$*}"
