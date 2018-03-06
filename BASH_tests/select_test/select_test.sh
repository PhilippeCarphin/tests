#
# This test demonstrates the select built-in:
#
# It has syntax like a for loop but it executes the body of the loop for each
# user input until said input is CTRL+D.
#

a=$(select f in $(ls) ; do printf "$f " ; echo "You chose $f" >&2 ; done)

# The echo's are captured into the variable a which we print.

echo "a is $a"
