




library_returner(){
    # false booggers
    return 1
    if $(( $1 % 2 == 0 )) ; then
        return ${1}
    else
        return 0
    fi

}
