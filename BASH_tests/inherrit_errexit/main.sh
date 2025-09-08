set -e
shopt -s inherit_errexit

func_containing_error(){
    echo "hello"
    echo "$(echo "subshell-hello" >&2 ; ls noexist ; echo "subshell-goodbye" >&2)"
    echo "goodbye"
}

func_returning_error(){

    return 1

}


func_containing_error

func_returning_error

echo "END"
