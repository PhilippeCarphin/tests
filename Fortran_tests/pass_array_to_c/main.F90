program pass_array_to_c

    use cprintarray
    use iso_c_binding
    use iso_fortran_env
    implicit none

    integer(C_INT) :: ni
    integer(C_INT) :: nj
    integer :: i,j
    real(C_FLOAT), dimension(:,:), allocatable :: array_2d
    real(C_FLOAT), dimension(:), allocatable :: array_1d

    ni = 8
    nj = 4
    allocate(array_2d(ni,nj))

    do i = 1,ni
        do j = 1,nj
            array_2d(i,j) = i + j/10.0
        enddo
    end do
    write(error_unit,*) "============= 8x4 Fortran array ============="
    write(error_unit,*) "============= 3 indexing methods"
    write(error_unit,*) "shape of array_2d: ", shape(array_2d)
    call cprint_array_2d_memory(array_2d, size(array_2d,1), size(array_2d,2))
    call cprint_array_2d_indexing(array_2d, size(array_2d,1), size(array_2d,2))
    call cprint_array_2d_array_yuck(size(array_2d,1), size(array_2d,2), array_2d)
    write(error_unit,*) "============= 8x4 Fortran array through Fortran adapters ============="
    write(error_unit,*) "============= Slice with step 2 demo array_2d(1:ni:2,1:nj:2)"
    call fprint_array(array_2d(1:ni:2,1:nj:2))
    write(error_unit,*) "============= Array 2d"
    call fprint_array(array_2d)
    write(error_unit,*) "============= Reshape demo"
    call fprint_array(reshape(array_2d,(/3,3/)))
    write(error_unit,'(4X8f4.1)') array_2d

    allocate(array_1d(ni*nj))
    do i = 1, ni*nj
        array_1d(i) = i
    end do

    write(error_unit,*) "============= Print 1d array as 2d"
    call cprint_array_2d_memory(array_1d, ni, nj)

    call fprint_array(array_1d)

end program
