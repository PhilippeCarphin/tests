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

end module

program main

    use, intrinsic :: iso_c_binding
    use, intrinsic :: iso_fortran_env
    use mainmod
    integer(kind=C_INT) :: forty_three = 43
    integer(kind=C_INT) :: eighty_six

    eighty_six = times_two(forty_three)

    eighty_six = times_two(int(forty_three, kind=C_LONG))

    two_hundred_and_fifty_eight = times_three(eighty_six)

    write(error_unit, *) "258 = ", two_hundred_and_fifty_eight

end program 
