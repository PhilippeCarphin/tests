
number=1000000
readonly TRUE=0

a=0
b=0
for ((i=0; i<number ; i++)) ; do
    if [[ ${a} == ${TRUE} ]] ; then
        ((b++))
    fi
done
echo $b

