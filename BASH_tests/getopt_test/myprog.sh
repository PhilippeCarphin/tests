#
# This script demonstrates the use of the 'getopt' executable to parse
# arguments in a bash script.  We could say that it does not actually
# parse the arguments but rearranges them in such a way that we can
# parse them ourselves in a simple loop.
#
# Getopt does some checking, reordering and splitting of arguments
# so that we can use the loop below.
# - Split '--fruit=apple' into '--fruit apple'
# - Split '-yf apple' into '-y -f apple'
# - Puts all non-option arguments after a '--'
# - Adds quoting so that the 'eval' can be reliable.
# - Adds empty argument after options that take optional argument
#   if no argument was provided: -v -yf apple -> -v '' -y -f 'apple'.
#
# Imagine how much more complicated the while loop would be if it had
# handle '--fruit=apple' and '--fruit apple' or '-yf apple' and there
# is also '-fapple' which is possible for options that have a required
# argument.
#
if ! normalized_arguments=$(getopt -n $0 -o yf:v:: --longoptions yes,fruit:,vegetable:: -- "$@") ; then
    echo "Argument parsing error"
    exit 1
fi

echo "Arguments before: $@" # -yf apple posarg1 --vegetable='baby carrot' posarg2
echo "Normalized arguments: ${normalized_arguments}"
eval set -- "${normalized_arguments}"
echo "Arguments after : $@" # -y -f apple --vegetable 'baby carrot' -- posarg1 posarg2
eval normalized_arguments_array=(${normalized_arguments})
for a in "${normalized_arguments_array[@]}" ; do
    echo "a='${a}'"
done

while : ; do
    case $1 in
        -y|--yes)       yes=1        ; shift   ;;
        -v|--vegetable) vegetable=$2 ; shift 2 ;;
        -f|--fruit)     fruit=$2     ; shift 2 ;;
        --) shift ; break ;;
        *) echo "Unhandled option : $1" ; exit 1 ;;
    esac
done

echo "Fruit = '${fruit}'"
echo "Vegetable = ${vegetable}"
echo "posargs = $@"
