module mainmod
    use, intrinsic :: iso_c_binding
    implicit none

    contains
        integer(kind=C_LONG) function times_two(cl)
            integer(kind=C_LONG), intent(in) :: cl
            times_two = 2*cl
        end function

        integer(kind=C_INT) function times_three(ci)
            integer(kind=C_INT), intent(in) :: ci
            times_three = 3*ci
        end function

        integer(kind=C_INT) function double_in_place(cl)
            integer(kind=C_LONG), intent(inout) :: cl
            cl = 2*cl
            double_in_place = 0
        end function


end module

program main

    use, intrinsic :: iso_c_binding
    use, intrinsic :: iso_fortran_env
    use mainmod
    implicit none
    integer(kind=C_INT) :: two_hundred_and_fifty_eight
    integer(kind=C_INT) :: forty_three = 43
    integer(kind=C_INT) :: eighty_six
    integer(kind=C_INT) :: ier

    ! Error (or maybe warning with some compilers): Wront type of argument
    !       passing INTEGER(4) to INTEGER(8)
    ! eighty_six = times_two(forty_three)

    eighty_six = times_two(int(forty_three, kind=C_LONG))

    two_hundred_and_fifty_eight = times_three(eighty_six)

    write(error_unit, *) "258 = ", two_hundred_and_fifty_eight

    ! Error Passing non-variable expression in variable definition context
    !       (actual argument to INTENT = OUT/INOUT)
    !       >>> Safe to use int(x,kind=Y) as the argument of a function because
    !           the compiler won't let us do it if it's to an OUT/INOUT arg
    ! ier = double_in_place(int(forty_three, kind=C_LONG))

end program 
