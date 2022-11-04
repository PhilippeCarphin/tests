# This is the slowest one everytime.  Not by enough that it would need
# that it would need to be purged from any script that uses this form
# but enough to refute the suggestion that this is the fastest way to
# do booleans in scripts.

if [[ "${number:-}" == "" ]] ; then
    echo "Please define the environment variable 'number' as an integer"
    exit 1
fi
declare -ri TRUE=0

a=0
b=0
for ((i=0; i<number ; i++)) ; do
    if [[ ${a} -eq ${TRUE} ]] ; then
        ((b++))
    fi
done
echo $b

