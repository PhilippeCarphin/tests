#!/bin/bash

#
# This test demonstrates funky stuff that that BASH does with PIDs
#
echo "$0: THIS_PID is $$"
echo "$0: PARENT_PID is ${PPID}"
echo -n "$0: PSTREE is "
pstree -p ${PPID}

#
# When we execute the script, bash does some kind of fork-exec,
# within the script, $$ gives some new PID, call it CHILD_PID and
# in this child ${PPID} expands to THIS_PID and CHILD_ID is the parent
# of the pstree process.
#
echo ""
echo "$0: Executing: ./script.sh"
./script.sh

#
# When we source the script, the commands are simply run by this shell's
# process.  So $$ expands to THIS_PID, ${PPID} expands to PARENT_PID
# and THIS_PID is the parent of the pstree process.
#
echo ""
echo "$0: Sourcing: source script.sh"
source ./script.sh

#
# In a subshell, a fork happens to create a process for the subshell,
# in the subshell process INTERMEDIATE_CHILD, a fork-exec happens to execute
# script.sh which creates CHILD. Within script.sh $$ expands to the PID of this
# CHILD, and ${PPID} expands to THIS_PID
#
echo ""
echo "$0: Executing in subshell: (./script.sh)"
( ./script.sh )

#
# This is where it gets interesting: a process is created for the subshell, but
# is a fork of this BASH process without an exec so although it creates a new
# process with a new PID, $$ and ${PPID} are not true ways of getting one's
# PID and parent PID but rather are ways to ask BASH to tell you what the PID
# and parent PID are.  And in that case, it gives those values for the process
# that created the subshell.
#
echo ""
echo "$0: Sourcing in subshell: (source ./script.sh)"
(source ./script.sh)

echo ""
echo "$0: Sourcing in subshell with ampersand: (source ./script.sh) & wait"
(source ./script.sh) & wait

echo ""
echo "it looks like starting a subshell starts a new process but BASH doesn't"
echo "want you to know about it"
(
    echo "subshell in ${BASH_SOURCE[0]}: \$\$ = $$"
    echo "pstree in subshell of ${BASH_SOURCE[0]}"
    pstree -p ${PPID}
    (echo "\$\$=$$,BASHPID=${BASHPID}" ; (echo "\$\$=$$,BASHPID=${BASHPID}" ; pstree -p ${PPID}))
)


