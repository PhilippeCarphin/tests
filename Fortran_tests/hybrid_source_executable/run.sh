
intel_fortran=""

if intel_fortran=$(which ifx 2>/dev/null) ; then
    intel_c=$(which icx)
elif intel_fortran=$(which ifort 2>/dev/null) ; then
    intel_c=$(which icc)
else
    echo "No Fortran intel compiler found"
    exit 1
fi

this_dir=$(cd -P $(dirname $0) && pwd)
rm -rf ${this_dir}/build-{intel,gcc}

printf "\033[1;37m==> Doing intel\033[0m\n"
echo "Running CMake ..."
cmake -S . -B build-intel -DCMAKE_C_COMPILER=${intel_c} -DCMAKE_Fortran_COMPILER=${intel_fortran} >/dev/null
echo "Cmake complete: $?"
cmake --build build-intel --target fmain
cmake --build build-intel --target main



printf "\033[1;37m==> Doing gcc\033[0m\n"
echo "Running CMake ..."
cmake -S . -B build-gcc -DCMAKE_C_COMPILER=$(which gcc) -DCMAKE_Fortran_COMPILER=$(which gfortran)
echo "Cmake complete: $?"
cmake --build build-gcc --target fmain
cmake --build build-gcc --target main

