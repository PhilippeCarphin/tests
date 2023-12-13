PROGRAM main
    use, intrinsic :: iso_fortran_env

    real, dimension(4,5) :: array_1, array_2
    integer :: i, j, n

    n = 1
    do i=1,4
        do j=1,5
            array_1(i,j) = n
            n = n+1
        enddo
    enddo
    write(error_unit, *) array_1
    array_2 = array_1
    write(error_unit, *) array_2

END PROGRAM
