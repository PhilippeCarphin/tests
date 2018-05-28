#!/bin/bash

echo =\$*=
echo $*
for x in $* ; do
   echo "x in \$* : $x"
done
echo =\$@=
echo $@
for x in $@ ; do
   echo "x in \$@ : $x"
done

shift

echo =\$*=
echo $*
for x in $* ; do
   echo "x in \$* : $x"
done
echo =\$@=
echo $@
for x in $@ ; do
   echo "x in \$@ : $x"
done
