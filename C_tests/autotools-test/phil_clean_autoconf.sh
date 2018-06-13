files="INSTALL\
 COPYING\
 config.log
 Makefile\
 Makefile.in\
 aclocal.m4\
 autom4te.cache/\
 compile\
 config.h.in\
 config.status\
 configure\
 depcomp\
 install-sh\
 missing\
 src/.deps/\
 src/Makefile\
 src/Makefile.in"
echo "$files"

for f in $files ; do
	rm -rf ./$f
done
