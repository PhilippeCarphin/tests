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
    write(error_unit,*) "shape of array_2d: ", shape(array_2d)
    call cprint_array_2d(array_2d, size(array_2d,1), size(array_2d,2))

    allocate(array_1d(ni*nj))
    do i = 1, ni*nj
        array_1d(i) = i
    end do

    call cprint_array_2d(array_1d, ni, nj)

    call fprint_array(array_1d)
    call fprint_array(array_2d)
    call fprint_array(array_2d(1:ni:2,1:nj:2))
    call fprint_array(reshape(array_2d,(/3,3/)))

end program
