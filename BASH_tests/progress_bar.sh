#!/bin/bash
#
# This is experimentation with the carrage return character.
#
for ((i=0;i<10;i=i+2)) ; do
	sleep 2
	for ((j=0;j<$i;j++)) ; do
		echo -n "#"
	done
	printf "\r"
	printf "\r x"
	printf "\rBonjour"
done

printf "\r"

sleep 1
printf "AA"
sleep 1
printf "BB"
sleep 1
printf "CC"

