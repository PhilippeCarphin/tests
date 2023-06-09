#
# This test demonstrates 'here documents' and 'here strings'.  Both are methods
# to use built-ins to send text to the STDIN of commands.
#

#
# For a long time, I thought the <<- (the '-' specifically) did not work as
# advertized probably because I read something that said that it would remove
# leading whitespace but when reading the bash man page, I read that it was
# only leading tabs.  So it turns out that it does work!
#
echo "======================"
var=variable_value
cat <<- END_OF_HERE_DOCUMENT
    leading spaces
	Leading tab
		Two leading tabs
	var=${var}
	$((1+2))
	END_OF_HERE_DOCUMENT


# Putting quotes on the delimiter word is a weird way of saying that we don't
# want ${}, $(), `` expansions to occur.
#
echo "======================"
cat <<- "END_OF_HERE_DOCUMENT"
    leading spaces
	Leading tab
		Two leading tabs
	var=${var}
	$((1+2))
	END_OF_HERE_DOCUMENT

#
# Send a string on STDIN without using echo
#
echo "======================"
cat <<< "hello
    bonjour
    goodbye"

