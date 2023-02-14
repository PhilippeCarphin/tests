#
# According to https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_03_02.html
# the underscore is a special variable that takes the name of the script being
# run at shell startup and subsequently takes the expanded value of the last
# argument of the previous command
test -n $(echo "${HOME}/booggers")
echo "_=${_}"
../../C_tests/underscore_special_var "A" $(echo "${USER}") "B"
echo "_=${_}"
