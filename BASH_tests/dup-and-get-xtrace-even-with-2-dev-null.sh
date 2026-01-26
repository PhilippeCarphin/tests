# This script demonstrates that by duplicating file descriptors:
#
#     exec {DUPFD}>&${FD}
#
# now DUPFD contains a file descriptor that refers to the same file/device as
# the original FD refers to.  However, running a command with ${FD}>/dev/null
# writing to DUPFD will still write to the original file/device.

# We test this here by using it to get XTRACE output to the shell for a function
# that is called with 2>/dev/null.
#
# NOTE: We could also do `exec {BASH_XTRACEFD}>/dev/tty` but this might not be
# possible in a batch job (I haven't tested it because even if it was possible,
# this solution is simpler and more elegant).

PS4=' + ${BASH_SOURCE[0]}:${FUNCNAME:-}:${LINENO}: '
exec {BASH_XTRACEFD}>&2
set -x

a-shell-function(){
    ls
    hostname
}

a-shell-function 2>/dev/null
