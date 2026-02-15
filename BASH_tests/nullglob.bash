# in tui-selector, I use bash_normpath and it stopped working when I had
# shopt -s nullglob.  It tooke me a while to figure out that was the difference
# but it turned out to be because the `new_tokens[i]` in `unset new_tokens[i]`
# is a glob expression that stays as is when `shopt -u nullglob` because it's
# quite unlikely I would have a file named `new_tokensi` in my current directory
# but with nullglob, `new_tokens[i]` expands to nothing! so the line becomes
# just `unset`
#
i=${1:-3}
shopt -p extglob # Does not make a difference
echo "======== Without nullglob =================="
array=(A B C D E F)
echo "array[i] glob expands to: " array[i]
unset array[i]
declare -p array

echo "======== With nullglob =================="
shopt -s nullglob
array=(A B C D E F)
echo "array[i] glob expands to: " array[i]
unset array[i]
declare -p array

echo "======== With nullglob and quotes =================="
shopt -s nullglob
echo "\"array[i]\" glob expands to: " "array[i]"
array=(A B C D E F)
unset 'array[i]'
declare -p array

echo ""
touch arrayi
echo "Created file arrayi"
echo "======== (WITH MATCH) Without nullglob =================="
array=(A B C D E F)
echo "array[i] glob expands to: " array[i]
unset array[i]
declare -p array

echo "======== (WITH MATCH) With nullglob =================="
shopt -s nullglob
array=(A B C D E F)
echo "array[i] glob expands to: " array[i]
unset array[i]
declare -p array

echo "======== (WITH MATCH) With nullglob and quotes =================="
shopt -s nullglob
echo "\"array[i]\" glob expands to: " "array[i]"
array=(A B C D E F)
unset 'array[i]'
declare -p array
rm -v arrayi
