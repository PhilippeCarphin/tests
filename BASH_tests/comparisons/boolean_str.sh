
number=1000000
a="true"
b=0
for (( i=0; i<number ; i++ )) ; do
    if [[ $a == true ]] ; then
        ((b++))
    fi
done
echo $b

