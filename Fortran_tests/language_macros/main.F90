program main
    use, intrinsic :: iso_fortran_env

#ifdef __STDC_VERSION__
    write(error_unit, '(a)') "__STDC_VERSION__ is YES defined"
#else
    write(error_unit, '(a)') "__STDC_VERSION__ is NOT defined"
#endif

end program

