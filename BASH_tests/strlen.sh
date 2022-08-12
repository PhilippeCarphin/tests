#
# Get the length of a string using ${#var_name}
#
# This test demonstrates that the value is different based on the value of
# LANG and LC_ALL.
#
# This assumes that your starting LANG/LC_ALL are not C otherwise there will
# be no difference.
#
# The bottom line is that ${#var_name} does not count the number of bytes but
# the number of characters according to the LANG/LC_ALL variables and that this
# will be equal to the number of bytes if LANG=C LC_ALL=C.
#
strU8DiffLen() {
    local charlen=${#1} LANG=C LC_ALL=C
    echo $(( ${#1} - charlen ))
}

for string in Généralités Language Théorème Février  "Left: ←" "Yin Yang ☯";do
    diff=$(strU8DiffLen "$string")
    printf " - %-$((14+$?))s is %2d chars length, but uses %2d bytes\n" "'$string'" ${#string} $((${#string}+${diff}))
done
