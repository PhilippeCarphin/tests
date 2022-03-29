this_file_zsh=$_

is_sourced_bash(){
    [[ "${BASH_SOURCE[0]}" != "${0}" ]]
}

is_sourced_zsh(){
    [[ $ZSH_EVAL_CONTEXT == toplevel* ]]
}

is_bash(){
    [[ $SHELL != zsh ]]
}

is_sourced(){
    if is_bash ; then
        is_sourced_bash
    else
        is_sourced_zsh
    fi
}

get_this_file(){
    if is_sourced ; then
        echo "Being sourced"
        if is_bash ; then
            echo "this_file = ${BASH_SOURCE[0]}"
        else
            echo "this_file = $this_file_zsh"
        fi
    else
        echo "Being run"
        if is_bash ; then
            echo "this_file = ${BASH_SOURCE[0]}"
        else
            echo "this_file = $0"
        fi
    fi
}

get_this_file

