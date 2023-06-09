function func_a(){
    local var=999
    echo "func_a: var=${var}"
    func_b
}

function func_b(){
    echo "func_b: var=${var}"
}

var=111
func_a
func_b
