
number=1000000

a=0
b=0
for ((i=0; i<number ; i++)) ; do
    if [[ ${a} == 0 ]] ; then
        ((b++))
    fi
done
echo $b

