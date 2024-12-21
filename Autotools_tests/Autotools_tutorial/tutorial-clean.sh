# Autoconf clean

if [[ -f Makefile ]] ; then
    make distclean
fi

# This is maybe some startup stuff that we would want to track
files=(
    Makefile.in
    aclocal.m4
    autoscan.log
    compile
    configure
    configure.scan
    depcomp
    missing
    install-sh
    srcx/Makefile.in
    config.phil.h.in
    ar-lib
    config.sub
    config.guess
    libtool
    ltmain.sh
)

dirs=(
    autom4te.cache
)

rm -fv "${files[@]}"
rm -rfv "${dirs[@]}"

configure_files=(
    Makefile.in
    Makefile
    config.log
    config.phil.h
    config.status
    stamp-h1
    srcx/Makefile.in
    srcx/Makefile
)

rm -fv "${configure_files[@]}"

rm -rfv localinstall

strict_files=(
    COPYING
    INSTALL
    NEWS
    README
    AUTHORS
    ChangeLog
)

for f in "${strict_files[@]}" ; do
    if [[ -L ${f} ]] ; then
        rm -v ${f}
    fi
done

