program nopreproc
    ! This file will be compiled without preprocessing unless the build system
    ! is ninja.
    use, intrinsic :: iso_fortran_env
    implicit none
    write(output_unit,*) "No preprocessor"
#if 0
    write(output_unit,*) "If preprocessor directives are read, this should not be printed"
#endif
    stop 0
end program
