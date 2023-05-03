#!/bin/bash

doit(){
    local build_type=$1
    local build_dir=build-${build_type}

    printf "\033[1;36mDOING BUILD TYPE : ${build_type}\033[0m\n"
    cmake -S . -B ${build_dir} -DCMAKE_BUILD_TYPE=${build_type} >/dev/null

    # cmake --build ${build_dir}
    (cd ${build_dir} && make --no-print-directory VERBOSE=1 | command grep --after-context=1 "Building C object\|Linking")

}

doit DEBUG
doit RELEASE
doit RELWITHDEBINFO
doit MINRELSIZE
