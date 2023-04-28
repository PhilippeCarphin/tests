echo "Doing the static version"
cmake -S . -B build-shared -DDO_MPI_STATIC_THING=OFF

echo "Doing the shared version"
cmake -S . -B build-static -DDO_MPI_STATIC_THING=ON
