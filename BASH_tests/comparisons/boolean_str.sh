
if [[ "${number:-}" == "" ]] ; then
    echo "Please define the environment variable 'number' as an integer"
    exit 1
fi
a="true"
b=0
for (( i=0; i<number ; i++ )) ; do
    if [[ $a == true ]] ; then
        ((b++))
    fi
done
echo $b

