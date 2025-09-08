
program main
    use, intrinsic :: iso_fortran_env
    use, intrinsic :: iso_c_binding
    use maybe_in_maybe_out_mod

    integer :: num,err
    num = 8
    write(*,*) "Normal call in IN mode with variable"
    err = maybe_in_maybe_out(num, 3,4)
    write(*,*) "Normal call in IN mode with constant literal"
    err = maybe_in_maybe_out(8, 7, 6)

    write(*,*) "Normal call in OUT mode with variable"
    num = 100
    err = maybe_in_maybe_out(num, 7, 6)
    write(*,*) ">>> num = ", num

    ! write(*,*) "Bad call in OUT mode with constant"
    ! Segfault here if we uncomment next line
    ! err = maybe_in_maybe_out(200, 8, 9)

end program
