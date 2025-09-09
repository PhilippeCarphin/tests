check(){
    printf "\033[1;37m%s\033[0m\n" "${cmd[*]}"
    "${cmd[@]}"
    ldd a.out | grep pthread
}
cmd=(gcc main.c -lpthread)
check

cmd=(gcc main.c -Wl,--as-needed -l pthread)
check

cmd=(gcc main.c -l pthread -Wl,--as-needed)
check
