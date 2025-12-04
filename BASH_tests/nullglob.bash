shopt -p extglob # Does not make a difference
echo "======== Without nullglob =================="
array=(A B C D E F)
i=${1:-3}
echo "array[i] glob expands to: " array[i]
unset array[i]
declare -p array

echo "======== With nullglob =================="
shopt -s nullglob
array=(A B C D E F)
i=${1:-3}
echo "array[i] glob expands to: " array[i]
unset array[i]
declare -p array

echo "======== With nullglob and quotes =================="
shopt -s nullglob
echo "\"array[i]\" glob expands to: " "array[i]"
array=(A B C D E F)
i=${1:-3}
unset 'array[i]'
declare -p array

echo ""
touch arrayi
echo "Created file arrayi"
echo "======== (WITH MATCH) Without nullglob =================="
array=(A B C D E F)
i=${1:-3}
echo "array[i] glob expands to: " array[i]
unset array[i]
declare -p array

echo "======== (WITH MATCH) With nullglob =================="
shopt -s nullglob
array=(A B C D E F)
i=${1:-3}
echo "array[i] glob expands to: " array[i]
unset array[i]
declare -p array

echo "======== (WITH MATCH) With nullglob and quotes =================="
shopt -s nullglob
echo "\"array[i]\" glob expands to: " "array[i]"
array=(A B C D E F)
i=${1:-3}
unset 'array[i]'
declare -p array
# Note array[i] as a glob would match the file arrayi so retry 
rm -v arrayi
