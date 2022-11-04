
if [[ "${number:-}" == "" ]] ; then
    echo "Please define the environment variable 'number' as an integer"
    exit 1
fi

declare -i a=0
declare -i b=0
for ((i=0; i<number ; i++)) ; do
    if (( a == 0 )) ; then
        ((b++))
    fi
done
echo $b

