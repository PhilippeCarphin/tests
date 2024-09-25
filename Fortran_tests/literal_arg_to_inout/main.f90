!
! Becasue in Fortran almost everything is passed by reference (like passing
! pointers in C) functions can modify their arguments in the outer scope
program main
    use, intrinsic :: iso_fortran_env
    implicit none

    integer :: my_number
    integer :: res

    my_number = 3
    res = getnum(my_number)
    write(error_unit, *) "my_number = ", my_number, "res = ", res

    res = getnum(0)
    write(error_unit, *) "my_number = ", my_number, "res = ", res

    contains
        integer function getnum(x)
            integer, intent(INOUT) :: x

            if(modulo(x,3) == 1) then
                x = 3*x
            else
                x = 2*x
            endif
            getnum = x
            return
        end function

end program
