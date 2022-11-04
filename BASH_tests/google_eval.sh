some_function(){
    echo "A B C"
    echo "DEFGH"
}

variable="$(eval some_function)"

echo "Variable has value '${variable}'"
