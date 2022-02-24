#
# This test demonstrates the select built-in:
#
# It has syntax like a for loop but it executes the body of the loop for each
# user input until said input is CTRL+D.
#
# The variable 'f' takes on the value associated with the number entered by
# the user.

select f in $(ls) ; do
    if [[ "$f" != "" ]] ; then
        a=$f
        break
    else
        printf "Please use the numbers to make a selection\n"
    fi
done
# The echo's are captured into the variable a which we print.

echo "a is $a"
