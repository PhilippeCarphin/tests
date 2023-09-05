#
# This test shows that we can use 'set' inside a function to control '$@' and
# $1, $2, etc inside the function and that this does not affect the value of
# '$@', $1, ..., in the outer scope
#
function func(){
    # Modifies '$@' only as seen inside the function
    eval set -- '"W X Y" Z'
    echo "@ = $@"
    echo "# = $#"
}

eval set -- 'A B C D "E F"'
echo "@ = $@"
echo "# = $#"

func

# Outer scope value of '$@' stays unchanged even if the function used 'set'
echo "@ = $@"
echo "# = $#"
