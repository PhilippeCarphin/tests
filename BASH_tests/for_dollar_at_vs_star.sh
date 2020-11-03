# set -- A B C "D  E   F" G H I

echo "=============== NO QUOTES ======================="
echo '========= for arg in $@ ========='
echo '$@='$@
echo 'nblem='${#@}
for arg in $@ ; do
    echo "arg = '$arg'"
done

echo '========= for arg in $* ========='
echo '$*='$*
echo 'nbelem='${#*}
for arg in $* ; do
    echo "arg = '$arg'"
done

echo "================== WITH QUOTES =================="
echo '========= for arg in "$@" ========='
echo '$@='$@
echo 'nblem='${#@}
for arg in "$@" ; do
    echo "arg = '$arg'"
done

echo '========= for arg in "$*" ========='
echo '$*='$*
echo 'nbelem='${#*}
for arg in "$*" ; do
    echo "arg = '$arg'"
done

echo "=================== THE DEFAULT (for w; do) =================="
for arg; do
    echo "arg = '$arg'"
done

