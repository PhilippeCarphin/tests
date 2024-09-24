trap 'echo "This is the global EXIT trap"' EXIT
# This test demonstrates a special behavior of traps in BASH:
#
# In general, when a subshell exits the exit trap is not run
# as is demonstrated by the first subshell.
# - We can run `trap -p EXIT` inside the subshell and we
#   see the global trap.
# - When the subshell exits, this trap is not run.  This is the
#   behavior we are used to.
#
# However, in the second subshell we set a trap on EXIT and this time
# the trap is run when the subshell exits.  This is something unexpected
# but it does make some sense.  Setting a trap in a subshell has no effect
# on the parent process therefore the only reason a user would set a trap
# in a subshell is because they want the trap to be run when the subshell
# exits.

echo "========== subshell where we don't set an exit trap inside =============="
(
    echo "begin subshell"
    trap -p EXIT
    echo "Exiting subshell"
)

echo "After the subshell"

echo "========== subshell in which we do set an exit trap ====================="
(
    echo "Begin subshell 2"
    trap -p EXIT
    trap "echo 'This is the subshell EXIT trap !!!!'" EXIT
    echo "Exiting subshell 2"
)

echo "After the 2nd subshell"
echo "End of script"
