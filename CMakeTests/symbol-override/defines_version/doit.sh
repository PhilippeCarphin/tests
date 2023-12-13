set -eEuo pipefail

main(){
    doit_one OFF OFF
    doit_one OFF ON
    doit_one ON OFF
    doit_one ON ON
}

doit_one(){
    local USE_OVERRIDES=${1}
    local WITH_SHADES=${2}
    local build_dir=build-${USE_OVERRIDES}_${WITH_SHADES}

    # CONFIGURE
    local cmd=(cmake -S . -B ${build_dir} -DUSE_OVERRIDES=${USE_OVERRIDES} -DWITH_SHADES=${WITH_SHADES})
    printf "\033[1;37m===>\033[0m ${cmd[*]}\033[0m\n"
    "${cmd[@]}" >/dev/null

    # BUILD
    cmake --build ${build_dir} &>/dev/null

    # RUN
    local result=$(${build_dir}/main | grep -o 'ORIGINAL\|CUSTOM\|OVERRIDE')

    # DISPLAY
    display_result
}

display_result(){

    local color
    if [[ ${USE_OVERRIDES} == ON ]] ; then
        if [[ ${result} == CUSTOM ]] || [[ ${result} == OVERRIDE ]] ; then
            color="\033[1;34m"
        else
            color="\033[1;35m"
        fi
    else
        if [[ ${result} == CUSTOM ]] || [[ ${result} == OVERRIDE ]] ; then
            color="\033[1;34m"
        else
            color="\033[1;35m"
        fi
    fi
    printf "Overrides: ${color}%3s\033[0m, Shades: %3s ===> ${color}${result}\033[0m\n" "${USE_OVERRIDES}" "${WITH_SHADES}"
}

main
