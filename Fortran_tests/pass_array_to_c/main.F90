program pass_array_to_c

    use cprintarray
    use iso_c_binding
    use iso_fortran_env
    implicit none

    integer(C_INT) :: n_rows ! Number of rows = length of columns = height of array
    integer(C_INT) :: n_cols ! Number of columns = length of lines = width of array
    integer :: i,j
    real(C_FLOAT), dimension(:,:), allocatable :: array_2d
    real(C_FLOAT), dimension(:), allocatable :: array_1d

    n_rows = 8
    n_cols = 4
    allocate(array_2d(n_rows,n_cols))

    do j = 1,n_cols
        do i = 1,n_rows
            array_2d(i,j) = i + j/10.0
        enddo
    end do
    write(error_unit, *) "============================================================"
    write(error_unit, *) "* We create an array_2d(nxm) and we see here that          *"
    write(error_unit, *) "* elements (i,j) with the same 'i' are contiguous in       *"
    write(error_unit, *) "* memory and if we decide to think of the first index as   *"
    write(error_unit, *) "* as a row number and the second index as a column number  *"
    write(error_unit, *) "* then we can say that columns are contiguous in memory    *"
    write(error_unit, *) "* and say that FORTRAN arrays are stored in a column major *"
    write(error_unit, *) "* configuration.                                           *"
    write(error_unit, *) "============================================================"
    call cprint_array_1d_memory(array_2d, size(array_2d,1)*size(array_2d,2))

    write(error_unit, *) "=========================================================="
    write(error_unit, *) "* Formatted write traverses the array in memory order    *"
    write(error_unit, *) "* so the format '(8x4f51)' prints elements as they are   *"
    write(error_unit, *) "* seen in memory order and inserts a newline every 4     *"
    write(error_unit, *) "* elements, we need to transpose the array for it to be  *"
    write(error_unit, *) "* printed in the same way as we conceptualize it         *"
    write(error_unit, *) "=========================================================="
    write(error_unit, *) "============= Straight print"
    write(error_unit, *) array_2d
    write(error_unit, *) "============= Formatted print"
    write(error_unit,'(8x4f5.1)') array_2d
    write(error_unit, *) "============= Formatted print of transpose"
    write(error_unit,'(8x4f5.1)') transpose(array_2d)

    allocate(array_1d(n_rows*n_cols))
    do i = 1, n_rows*n_cols
        array_1d(i) = i
    end do

    ! write(error_unit,*) "============= Print 1d array as 2d"
    ! call cprint_array_2d_memory(array_1d, n_rows, n_cols)

    ! call fprint_array(array_1d)

end program
