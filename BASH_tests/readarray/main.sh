#!/usr/bin/env -S bash -o errexit -o nounset -o errtrace -o pipefail -O inherit_errexit -O nullglob -O extglob

cb(){
    # local i=0
    # for((i=0;i<=$#;i++)); do
    #     echo "${FUNCNAME[0]}: arg[$i]=${!i}"
    # done
    echo "readarray: doing element $(($1 + 1))" >&2
}

</usr/share/dict/linux.words readarray -C cb -c 50000 my_array
# declare -p my_array
