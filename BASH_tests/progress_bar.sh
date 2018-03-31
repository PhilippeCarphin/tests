#!/bin/zsh
#
# This is experimentation with the carrage return character.
#
for ((i=0;i<10;i=i+2)) ; do
	sleep 2
	for ((j=0;j<$i;j++)) ; do
		echo -n "#"
	done
	echo -n "\r"
	echo -n "\r x"
	echo -n "\rBonjour"
done

echo -n "\r"

sleep 1
echo -n "AA"
sleep 1
echo -n "BB"
sleep 1
echo -n "CC"

