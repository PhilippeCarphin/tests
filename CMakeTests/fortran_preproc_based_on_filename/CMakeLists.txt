cmake_minimum_required(VERSION 3.10)

project(preproc_demo Fortran)
#
# Files should get preprocessed or not based on the case of the 'f' in the
# extension.  Capital 'F' means preprocess and 'f' means no preprocessing
# I remember it by thinking that macros are typically written in all caps.
# To force preprocessing of all Fortran files, this line can be uncommented
# set(CMAKE_Fortran_PREPROCESS ON)
# https://cmake.org/cmake/help/latest/variable/CMAKE_Fortran_PREPROCESS.html
# https://cmake.org/cmake/help/latest/prop_tgt/Fortran_PREPROCESS.html
# Note that the CMAKE_Fortran_PREPROCESS "is used to initialize the
# Fortran_PREPROCESS property on all the targets".  This means that if it is
# given a value after a target is created, it will have no effect on that
# target.
#
# Note also that with Ninja, all Fortran source files are preprocessed no matter
# what to dynamically update module dependency order at build time (with Make,
# module dependency information is only gathered at configuration time).

#
# This file will not get passed through the preprocessor and so the '#include'
# will still be present when the file gets to the compiler.  The compiler will
# complain that there is a "bad/illegal" preprocessor directive but may,
# depending on the compiler, just issue a warning and treat the '#include' like
# it wasn't there
#
add_executable(nopreproc nopreproc.f90)

#
# Because of the capital 'F', the file will get passed through the preprocessor.
# This is done by CMake putting the proper flag to request this from the
# compiler.
#
add_executable(preproc   preproc.F90)

