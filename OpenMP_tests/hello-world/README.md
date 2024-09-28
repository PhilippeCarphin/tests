# OpenMP Hello World

The most basic OpenMP program

## CMake

We just need a `find_package(OpenMP)` which defines `OpenMP::OpenMP_C` and
`OpenMP::OpenMP_Fortran`.

Targets need to link with one of the two targets above to use openmp stuff.

## Code

In C a for loop can be parallelized by preceding it with `#pragma omp parallel
for` and in Fortran, a `do` loop can be parallelized by preceding it with
`!$omp parallel do`

Note that `omp_get_num_threads()` needs to be inside an OpenMP thing to return
something else than 1.
