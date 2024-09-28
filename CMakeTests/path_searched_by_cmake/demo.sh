printf "==========================================================================\n"
printf "PART 1: Demonstrating that if <X>/bin or <X> where <X> is the project prefix
is in PATH, then find_package can find the project\n"
printf "==========================================================================\n"
printf "\033[1;37mWithout anything dummy_project is not found:\033[0m\n"
build=$(mktemp -d build.XXXXXX)
cmake -S . -B ${build} 2>&1 | grep -i dummy
rm -rf "${build}"
printf "\033[1;37mdummy_project_prefix/bin in PATH\033[0m\n"
(
    export PATH=${PWD}/dummy_project_prefix_path/bin:${PATH}
    build=$(mktemp -d build.XXXXXX)
    cmake -S . -B ${build} 2>&1 | grep -i dummy
    rm -rf "${build}"
)
printf "\033[1;37mdummy_project_prefix in PATH\033[0m\n"
(
    export PATH=${PWD}/dummy_project_prefix_path:${PATH}
    build=$(mktemp -d build.XXXXXX)
    cmake -S . -B ${build} 2>&1 | grep -i dummy
    rm -rf "${build}"
)
printf "==========================================================================\n"
printf "PART 2: Determining the precedence order of the various known way in
which find_package can find our project\n"
printf "==========================================================================\n"
printf "\033[1;37mPrecedence: all 5\033[0m\n"
(
    export dummy_project_DIR=${PWD}/dummy_project_prefix_DIR
    export dummy_project_ROOT=${PWD}/dummy_project_prefix_ROOT
    export PATH=${PWD}/dummy_project_prefix_path/bin:${PATH}
    export CMAKE_PREFIX_PATH=${PWD}/dummy_project_prefix_env${CMAKE_PREFIX_PATH:+:${CMAKE_PREFIX_PATH}}
    build=$(mktemp -d build.XXXXXX)
    cmake -S . -B ${build} -DCMAKE_PREFIX_PATH=$PWD/dummy_project_prefix_cmake 2>&1 | grep -i dummy
    rm -rf "${build}"
)
printf "\033[1;37mPrecedence: cmake, DIR, env, path\033[0m\n"
(
    export dummy_project_DIR=${PWD}/dummy_project_prefix_DIR
    export PATH=${PWD}/dummy_project_prefix_path/bin:${PATH}
    export CMAKE_PREFIX_PATH=${PWD}/dummy_project_prefix_env${CMAKE_PREFIX_PATH:+:${CMAKE_PREFIX_PATH}}
    build=$(mktemp -d build.XXXXXX)
    cmake -S . -B ${build} -DCMAKE_PREFIX_PATH=$PWD/dummy_project_prefix_cmake 2>&1 | grep -i dummy
    rm -rf "${build}"
)

printf "\033[1;37mPrecedence: DIR, env, path\033[0m\n"
(
    export dummy_project_DIR=${PWD}/dummy_project_prefix_DIR
    export PATH=${PWD}/dummy_project_prefix_path/bin:${PATH}
    export CMAKE_PREFIX_PATH=${PWD}/dummy_project_prefix_env${CMAKE_PREFIX_PATH:+:${CMAKE_PREFIX_PATH}}
    build=$(mktemp -d build.XXXXXX)
    cmake -S . -B ${build}  2>&1 | grep -i dummy
    rm -rf "${build}"
)

printf "\033[1;37mPrecedence: env, path\033[0m\n"
(
    export PATH=${PWD}/dummy_project_prefix_path/bin:${PATH}
    export CMAKE_PREFIX_PATH=${PWD}/dummy_project_prefix_env${CMAKE_PREFIX_PATH:+:${CMAKE_PREFIX_PATH}}
    build=$(mktemp -d build.XXXXXX)
    cmake -S . -B ${build}  2>&1 | grep -i dummy
    rm -rf "${build}"
)

printf "Order determined by trying once with everything, then removing the winner to see who gets picked next\n"
printf "then removing the winner and so on...\n"
printf "Results are \n"
printf " 1: <X>_ROOT\n"
printf " 2: CMAKE_PREFIX_PATH cmake variable\n"
printf " 3: <X>_DIR env var\n"
printf " 4: CMAKE_PREFIX_PATH env var\n"
printf " 5: PATH env var\n"
