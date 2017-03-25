boner=

if [[ -n $boner ]]; then
	echo "If reussi"
else
	echo "if échoué"
fi

echo "definition non nulle"
boner=ABCD

if [[ -n $boner ]]; then
	echo "If reussi"
else
	echo "if échoué"
fi

# Now I prefer the following because it has the advantage of being easily
# understandable.  No need to look up what -n does.

variable=
if [[ $variable == "" ]]; then
	echo "variable is empty"
else
	echo "variable is not empty"
fi

echo "definition non nulle"
variable=asdf

if [[ $variable == "" ]]; then
	echo "variable is empty"
else
	echo "variable is not empty"
fi
