
cmd=$1

COMP_LINE="$*"
COMP_WORDS=("$@")
COMP_POINT=${#COMP_LINE}
COMP_CWORD=$((${#COMP_WORDS[@]}-1))
COMPREPLY=()
echo "${COMP_CWORD}"

compspec=($(complete -p ${cmd}))
i=0
while (( i < ${#compspec[@]} )) ; do
    case ${compspec[i]} in
        -o) i=$((i+1)) ;;
        -F) completion_func=${compspec[i+1]} ; break ;;
        -C) completion_cmd=${compspec[i+1]} ; break ;;
        *) echo "WARNING: Unhandled option '${compspec[i]}'"
    esac
done

if [[ -n ${completion_func} ]] ; then
    ${completion_func}
    echo "COMPREPLY=(${COMPREPLY[@]})"
elif [[ -n ${completion_cmd} ]] ; then
    export COMP_TYPE COMP_KEY
    ${completion_cmd} ${cmd} ${COMP_WORDS[COMP_CWORD]} ${COMP_WORDS[COMP_CWORD-1]}


__git_wrap__git_main
echo ${COMPREPLY[@]}
