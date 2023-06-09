#
# This test demonstrates that a new process is created for a pipe even though
# we are synchronously executing shell functions.
#
function my_true_pid(){
    echo "sending '${FUNCNAME[0]}:${BASHPID}' down to STDOUT" >&2
    echo "${FUNCNAME[0]}:${BASHPID}"
}

function pipe_end(){
    read l
    echo "${FUNCNAME[0]}: read '${l}'"
    echo "${FUNCNAME[0]}: my BASHPID is ${BASHPID}"
}

echo "${FUNCNAME[0]}: \$\$ = $$"
echo "${FUNCNAME[0]}: BASHPID=${BASHPID}"

#
# This function call does not cause a child process to be created.
#
my_true_pid

#
# This causes at least two new processes to be created.
#
my_true_pid | pipe_end

