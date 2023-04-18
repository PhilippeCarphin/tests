
if ! (return 0 2>/dev/null) ; then
    echo "ERROR: This file must be sourced"
    exit 1
fi

trap 'trap "" ERR ; return 1' ERR

ls noexist

echo "End of script"

trap "" ERR


