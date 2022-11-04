
if [[ "${number:-}" == "" ]] ; then
    echo "Please define the environment variable 'number' as an integer"
    exit 1
fi

a=0
b=0
for ((i=0; i<number ; i++)) ; do
    if [[ ${a} == 0 ]] ; then
        ((b++))
    fi
done
echo $b

