
for i in 3 2 1 ; do
	(echo "Launched sleep $i" ; sleep $i ; echo "Sleep $i done") &
done

wait
