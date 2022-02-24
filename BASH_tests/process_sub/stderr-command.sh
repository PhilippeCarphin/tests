while read the_line ; do
    echo "$1 - $the_line" >&2
done
echo "Output of stderr command" >&2
