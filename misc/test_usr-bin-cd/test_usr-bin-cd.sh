#!/bin/sh

#!/bin/bash

################## /usr/bin/cd ################################
# #!/bin/sh
# # $FreeBSD: src/usr.bin/alias/generic.sh,v 1.2 2005/10/24 22:32:19 cperciva Exp $
# # This file is in the public domain.
# builtin `echo ${0##*/} | tr \[:upper:] \[:lower:]` ${1+"$@"}
###############################################################

# I was looking at man pages and found out some builtins have a non-builtin
# version, so I looked at /usr/bin/cd and found out that commands like it all
# are made script.  The ${1+"$@"} intrigued me as I thought that the smartquotes
# around '$@' did what it looks to me like that ${1+...} was for.

# I thought this ${1+"$@"} makes it so that the command does not have an empty
# string argument if the script receives no arguments.
#
# With bash that seems to not be necessary.  print_args.sh prints the number of
# arguments and it prints the same number for both.
#

# Arguments with spaces stay as single arguments
# no empty-string argument for print_args if $# == 0.
echo 'print_args.sh "$@"'
./print_args.sh "$@"

# Same result as above (I think the smart quotes make the ${1+ thing not useful
echo 'print_args.sh ${1+"$@"}'
./print_args.sh "${1+$@}"

# Args with spaces get separated
# No empty string arg for print_args if $# == 0
echo 'print_args.sh ${1+$*}'
./print_args.sh ${1+$*}
./print_args.sh $*

# No in-between for '$*'.  Smart quotes only work for '$@'.
# Without quotes, '$*' splits up arguments that have spaces.
# With quotes '$*' becomes a single argument.

# Combines all arguments
# empty string argument for print_args if $# == 0.
echo 'print_args.sh ${1+$*}'
./print_args.sh "${1+$*}"
