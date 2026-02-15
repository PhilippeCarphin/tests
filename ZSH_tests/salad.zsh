salad(){
    echo "salad function called"
    echo "Args are $*"
}

_salad_fruits=(apple apricot bananna cherry)
_salad_vegetables=(carrot onion potato celery)
_salad_options=(--fruit --vegetable)

_salad(){
    local cur="${words[-1]}"
    local prev="${words[-2]}"
    case "${prev}" in
        --fruit|-f) compadd -a _salad_fruits ;;
        --vegetable|-v) compadd -a _salad_vegetables ;;
        *) compadd -a _salad_options ;;
    esac
}

compdef _salad salad
