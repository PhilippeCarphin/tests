doit(){
    dir=$1 ; shift
    printf "\033[1;37m ${dir}: ===> $@ \033[0m\n"
    (
        mkdir -p ${dir}
        cd ${dir}
        set -x
        cmake .. "$@"
    )
}

rm -rf build-default build-usr-local build-other
# No -DCMAKE_INSTALL_PREFIX: both methods come to the conclusion that the user
# has not provided an install prefix
doit build-default
# But if the user does provide an install prefix that happens to be equal to
# /usr/local, the first IF would erroneously come to the conclusion that the
# user has not provided an install prefix.
doit build-usr-local -DCMAKE_INSTALL_PREFIX=/usr/local
# Of course if the user provides an install prefix, then both methods of checking
# produce the same result but using CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT
# is clearer.
doit build-other -DCMAKE_INSTALL_PREFIX=../localinstall
# Therefore, the clearer and more reliable method is to use
# CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT


