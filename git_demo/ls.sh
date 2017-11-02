for f in $(cat list) ; do
	echo -n "$f "
	cat -n $f
done
