
function has_errexit()
{
    shopt -op errexit
}

echo "DEMO:"
shopt -op errexit
echo "exit code was $?"

if has_errexit ; then
    echo "HAS ERREXIT"
else
    echo "NO ERREXIT"
fi

set -e

echo "2 - \$* = '$*'"
shopt -op errexit
echo "exit code was $?"

if has_errexit ; then
    echo "HAS ERREXIT"
else
    echo "NO ERREXIT"
fi


if shopt -op errexit >/dev/null 2>&1
    user_had_errexit=true
else
    user_had_errexit=false
fi

set +e
# Do things with 'clever' if statements

if [[ "${user_had_errexit}" == true ]] ; then
    set -e
fi 
