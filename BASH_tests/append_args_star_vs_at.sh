#!/bin/bash
echo $@

echo -e "Starting with arguments \$1 = '1 1' and \$2 = '2',
Appeding arguments '3' and '4', after that, we should
still have \$1 = '1 1'.  Out of

    \$*, \"\$*\", \$@, \"\$@\",

only the last one does it correctly"
set -- '1 1' 2
set -- $* 3 4
echo -e "  \$* : \$1 = $1     \033[31m✗\033[m"

set -- '1 1' 2
set -- $@ 3 4
echo -e "  \$@ : \$1 = $1     \033[31m✗\033[m"

set -- '1 1' 2
set -- "$*" 3 4
echo -e "\"\$@\" : \$1 = $1 \033[31m✗\033[m"

set -- '1 1' 2
set -- "$@" 3 4
echo -e "\"\$@\" : \$1 = $1   \033[32m✓\033[m"
