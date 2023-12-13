
function test-path-like-var(){
    #local path_like_var=${1:+${1}${2:+:$2}}
    local path_like_var

    if [[ -n "$1" ]] ; then
        path_like_var=${path_like_var:+${path_like_var}:}${1}
    fi

    if [[ -n "$2" ]] ; then
        path_like_var=${path_like_var:+${path_like_var}:}${2}
    fi

    echo "path_like_var='${path_like_var}'"
    if [[ "${path_like_var}" != "${3}" ]] ; then
        echo ">>> FAIL: expected '$3'"
    fi
}

test-path-like-var ""  ""  ""
test-path-like-var "a" "b" "a:b"
test-path-like-var ""  "b" "b"
test-path-like-var "a" ""  "a"
