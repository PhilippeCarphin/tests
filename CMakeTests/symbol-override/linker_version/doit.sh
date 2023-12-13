set -eEuo pipefail

doit_one(){
    local USE_OVERRIDES=${1}
    local WITH_SHADES=${2}
    local build_dir=build-USE_OVERRIDES-${USE_OVERRIDES}__WITH_SHADES-${WITH_SHADES}
    cmd=(cmake -S . -B ${build_dir} -DUSE_OVERRIDES=${USE_OVERRIDES} -DWITH_SHADES=${WITH_SHADES})
    printf "\033[1;37m ===> \033[0m${cmd[*]}\033[0m\n"
    if "${cmd[@]}" | grep Warning &>/dev/null ; then
        exit 1
    fi
    cmake --build ${build_dir} &>/dev/null
    local result=$(${build_dir}/main | grep -o 'ORIGINAL\|CUSTOM\|OVERRIDE')
    local color
    if [[ ${USE_OVERRIDES} == ON ]] ; then
        if [[ ${result} == CUSTOM ]] || [[ ${result} == OVERRIDE ]] ; then
            color="\033[1;32m"
        else
            color="\033[1;31m"
        fi
    else
        if [[ ${result} == CUSTOM ]] || [[ ${result} == OVERRIDE ]] ; then
            color="\033[1;31m"
        else
            color="\033[1;32m"
        fi
    fi

    printf "Overrides: %3s, Shades: %3s ===> ${color}${result}\033[0m\n" "${USE_OVERRIDES}" "${WITH_SHADES}"
}

doit_one OFF OFF
doit_one OFF ON
doit_one ON OFF
doit_one ON ON
