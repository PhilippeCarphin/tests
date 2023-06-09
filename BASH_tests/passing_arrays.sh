
function returns_array(){
    array=("apple" apricot "bannana smoothie" "cherry pie")
    echo "${array[*]}"
}

function get_array(){
    local save_ifs="${IFS}"
    local IFS=$(printf "8")
    local retval=( $(returns_array) )
    IFS=${save_ifs}
    for a in "${retval[@]}" ; do
        echo "a=${a}"
    done
    for b in ${retval[@]} ; do
        echo "b=${b}"
    done
    local nb_elem=${#retval[@]}
    if [[ ${nb_elem} == 4 ]] ; then
        echo "Success: 4 elements"
    else
        echo "Fail: expected 4 elements, got ${nb_elem}"
    fi
}

get_array
