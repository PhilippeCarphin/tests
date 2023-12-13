
rm -rf build-default
cmd=(cmake -S . -B build-default)
printf "Runing '${cmd[*]}' with no environment variable\n"
"${cmd[@]}" | command grep -v '^--'

rm -rf build-env
export WITH_MY_THING="FALSE"
cmd=(cmake -S . -B build-env)
printf "Runing '${cmd[*]}' with environment variable equal to '${WITH_MY_THING}'\n"
"${cmd[@]}" | command grep -v '^--'

rm -rf build-cli
cmd=(cmake -S . -B build-cli -DWITH_MY_THING=TRUE)
printf "Runing '${cmd[*]}' with environment variable equal to '${WITH_MY_THING}'\n"
"${cmd[@]}" | command grep -v '^--'
