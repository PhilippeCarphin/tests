program main
    !
    ! This program demonstrates how to convert two nested loops sharing a
    ! "DO termination statement".  This solves the warning:
    !
    !   Sharing of a DO termination statement by more than one DO statement is
    !   an obsolescent feature in Fortran 2008.  Use an END DO or CONTINUE
    !   statement for each DO statement.   [10]
    !
    use, intrinsic :: iso_fortran_env
    implicit none
    integer :: i,j

    do 10 i=0,5
    do 10 j=0,3
        write(output_unit,"('('i1,',',i1,')')", advance="no") i,j
        if(j .eq. 3) then
            write(output_unit,*)
        endif
10  continue

    write(output_unit,*) "========================================="
    do i=0,5
        do j=0,3
            write(output_unit,"('('i1,',',i1,')')", advance="no") i,j
        enddo
        write(output_unit,*)
    enddo

end program
