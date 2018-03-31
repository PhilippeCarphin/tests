# Read a line from commands.txt and run it in background
while read c ; do
	(eval $c) &
done < commands.txt

wait
