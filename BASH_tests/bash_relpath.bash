# Based on the python implementation os.path.relpath() except that I make paths
# absolute using $PWD instead of python's os.getcwd() which can maybe make a
# difference when we have paths that have ..'s in them and there are links
# involved.
#
# Let path, start be absolute paths (made absolute by prepending PWD if they are
# not absolute)
#
# Decompose path into ${common_part}/${path_rest}
# and start into ${common_part}/${start_rest}
#
# Let dot_dots be '../' * number of components in start_rest.  So that
# ${start}/${dot_dots} normalizes to ${common_part}
#
# Therefore, with relpath=${dot_dots}/${path_rest}, we have
#      ${start}/${relpath} ~ ${start}/${dot_dots}/${path_rest}
#                          ~ ${common_part}/${path_rest}
#                          ~ ${path}
# where '~' means 'are equal when normalized'.
min(){ if (($1 > $2)) ; then echo "$1" ; else echo "$2" ; fi ; }
bash-relpath(){
    local path="${1}"
    local start="${2:-${PWD}}"
    local IFS="/"
    if [[ $path != /* ]] ; then path=${PWD}/${path} ; fi
    if [[ $start != /* ]] ; then start=${PWD}/${start} ; fi
    local path_list=(${path#/})
    local start_list=(${start#/})
    local rel_list=()

    local nb_common=$(min ${#start_list[@]} ${#path_list[@]})
    for((i=0; i<nb_common; i++)); do
        if [[ ${path_list[i]} != ${start_list[i]} ]] ; then
            nb_common=$i
            break
        fi
    done

    for((i=0; i<${#start_list[@]}-nb_common; i++)) ; do
        rel_list+=('..')
    done

    for((i=nb_common; i<${#path_list[@]} ; i++)); do
        rel_list+=(${path_list[i]})
    done
    if ((${#rel_list[@]} == 0)) ; then
        echo "."
    else
        echo "${rel_list[*]}"
    fi
}

bash-relpath-test-py(){
    printf "path=$1, start=$2\n"
    local path=${1}
    local expected=${2}
    value=$(bash-relpath "$@")
    expected=$(python3 -c 'import os,sys; print(os.path.relpath(sys.argv[1],start=sys.argv[2]))' "$@")
    if [[ ${value} != ${expected} ]] ; then
        printf "    FAIL: EXPECTED=${expected}\n" >&2
        printf "          GOT=${value}\n" >&2
        return 1
    else
        printf "    SUCCESS: GOT=${value}\n" >&2
    fi
}
bash-relpath-test-py "/User/pcarphin/Repositories/github.com/philippecarphin/repos/localinstall" "/User/pcarphin/fs1/Cellar"
bash-relpath-test-py "/User/pcarphin/Repositories/github.com/philippecarphin/repos/localinstall" "/User/pcarphin/fs1"
bash-relpath-test-py "/User/pcarphin/Repositories/github.com/philippecarphin/repos/localinstall" "/User/pcarphin/Repositories/github.com/philippecarphin/repos/localinstall"
bash-relpath-test-py "/User/pcarphin/Repositories/github.com/philippecarphin/repos/localinstall" "/etc"
