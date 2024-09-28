program main

    use grid_mod
    use, intrinsic :: iso_c_binding
    use, intrinsic :: iso_fortran_env
    implicit none

    integer :: cmp, err
    character :: chr

    TYPE(tgrid) :: the_grid

    err =  string_to_array("OCEAN", the_grid%Id, .false.)
    if(err .ne. 0) then
        write(error_unit, *) "Failed to copy 'OCEAN' into the_grid%Id"
    endif

    ! the_grid%Id = transfer("OCEAN" // c_null_char, the_grid%Id)

    the_grid%NI = 1337

    cmp = grid_print(the_grid)
    if(cmp .ne. 0) then
        write(error_unit,*) "I wanted 'OCEAN' but got '", the_grid%Id, "'"
        stop 1
    else
        write(error_unit,*) "SUCCESS: I wanted 'OCEAN' and I got '", the_grid%Id, "'"
    endif

contains
        !
        ! Convert a string of length N into an array of N+1 strings of length 1
        ! setting the N+1-th string to be a single c_null_char
        !
        integer function string_to_array(scalar, array, fill_spaces)
            use, intrinsic :: iso_fortran_env
            use, intrinsic :: iso_c_binding

            character(len=*), intent(IN) :: scalar                    ! One string of length N
            character(len=1), dimension(:), intent(OUT) :: array      ! N strings of length 1
            logical, intent(IN) :: fill_spaces

            integer :: i
            integer :: in_len
            integer, dimension(1) :: out_shape

            in_len = len_trim(scalar)
            out_shape = shape(array)

            if(out_shape(1) < in_len+1) then
                write(error_unit,*) "string_to_array: ERROR: Output is too small: ", out_shape(1), "need ", in_len+1
                string_to_array = 1
                return
            endif

            do i=1,in_len
                array(i) = scalar(i:i)
            enddo

            array(in_len+1) = c_null_char
            array(9) = ' '
            write(*,*) "Length of array(8): ", len(array(8))
            write(*,*) "value of array(9): '", array(9), "'"
            write(*,*) "value of array(10): '", array(10), "'"

            if(fill_spaces) then
                ! If I add this part, the print at line 25 gives 'OCEAN        '
                ! but if I don't, then it prints 'OCEAN'.  Arent't all those
                ! array elements already equal to ' '?
                ! For C it doesn't change anything, it stops at the c_null_char
                ! but for FORTRAN, I don't understand.
                do i=in_len+2,out_shape(1)
                    array(i) = ' '
                enddo
            endif

            string_to_array = 0
            return
        end function

end program
