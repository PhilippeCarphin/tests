#!/bin/bash

set -euEo pipefail
shopt -s inherit_errexit

#
# This test shows that it is OK to have a case statement inside a $() even
# though vim's syntax highlighting makes it look like a syntax error.
#
# Usually vim's syntax highlighting is a pretty good way of noticing that
# something is wrong.  But here it just gets confused by the unmatched closing
# parentheses in the case.
#
# The following works even though it really looks like it doesn't.
#
x=$(case ${1-} in a) echo "AAA" ;; b) echo "BBB" ;; c) echo "CCC" ;; *) echo "***" ;; esac)
echo "x=$x"
