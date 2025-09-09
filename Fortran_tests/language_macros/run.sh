doit(){
    echo "    $*"
    (eval "$@" 2>&1) | sed 's/^/    /'
}
echo "GCC C Code"
doit "gcc main.c && ./a.out"
echo "GCC F Code"
doit "gfortran main.F90 && ./a.out"
echo "Intel C Code"
doit "icx main.c && ./a.out"
echo "Intel F Code"
doit "ifx main.F90 && ./a.out"

rm -f a.out
