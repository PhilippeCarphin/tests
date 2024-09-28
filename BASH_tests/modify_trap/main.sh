#
# This test demonstrates how to get the code of current trap for a signal.
# We first demonstrate how to simply save and restore a trap using the output
# of 'trap -p ERR'.  But to augment or modify a trap, we need to get the
# code of the trap from the output of 'trap -p ERR'.
#
# Note that the output of `trap -p` requires an `eval`.  This is so that quotes
# that it may contain will be interpreted correctly.  See at the end of this file
#
trap 'echo "Original ERR trap"' ERR

#
# Save and restore trap
#
echo "==== First part, is trap restored ..."
restore_trap="$(trap -p ERR)"   # Save
trap 'echo "New ERR trap"' ERR  # Change
eval "${restore_trap}"          # Restore
trap -p ERR                     # Confirm restored

#
# Modify/augment a trap
#
echo "==== Second part, was trap modified ..."
eval original_trap=("$(trap -p ERR)") # Get original
trap "${original_trap[2]} >&2" ERR    # Augment (add '>&2')
trap -p ERR                           # Confirm augmented


#
# Examples of how trap -p outputs when the trap has single quotes and double
# quotes
#
echo "==== trap with double quotes"
trap "echo \"Hello World\"" ERR
trap -p ERR

echo "==== trap with single quotes"
trap "echo 'Hello World'
      echo 'how is everyone'" ERR
trap -p ERR

#
# Effect of quotes and eval on word splitting.  We see that without the eval
# we either get a single element with the whole output of 'trap -p err' or
# an incorrectly split mess.
#
# We need the eval.  We also need some quotes arouvd the `$(trap -p ERR)` in
# order to preserve whitespace characters.  Otherwise newlines can get turned
# into spaces and if these newlines separate commands, then losing them would
# give an incorrect result.
#
print_array(){
    local name=$1
    local -n ref=$1
    for((i=0; i<${#ref[@]}; i++)); do
        echo "${name}[$i]=${ref[i]}"
    done
}
echo "==== Word splitting without the eval"
echo "  with quotes"
array=("$(trap -p ERR)")
print_array array

echo "  without quotes"
array=($(trap -p ERR))
print_array array
echo "==== Word splitting with the eval"
echo "  with quotes"
eval array=("$(trap -p ERR)")
print_array array

echo "  without quotes"
eval array=($(trap -p ERR))
print_array array

#
# If the trap contains single quotes, for example
#
#       trap "echo 'hello world'" ERR
#
# then the output of trap -p ERR will be
#
#       trap 'echo '\''hello world'\'''
#                  cqqo
# where c is a closing single quote, qq is the character single quote, and o
# is an opening single quote.
#
# Without the eval, we get
