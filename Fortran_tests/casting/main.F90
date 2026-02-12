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

        real(kind=C_DOUBLE) function double_double(dbl)
            real(kind=C_DOUBLE), intent(in) :: dbl
            double_double = 2 * dbl
        end function

        real(kind=C_DOUBLE) function double_float(dbl)
            real(kind=C_FLOAT), intent(in) :: dbl
            double_float = 2 * dbl
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
    real(kind=C_DOUBLE) :: eighty_six_d
    real(kind=C_FLOAT) :: pi = 3.14159
    real(kind=C_FLOAT) :: two_pi

    ! Error (or maybe warning with some compilers): Wront type of argument
    !       passing INTEGER(4) to INTEGER(8)
    ! eighty_six = times_two(forty_three)

    eighty_six = times_two(int(forty_three, kind=C_LONG))

    two_hundred_and_fifty_eight = times_three(eighty_six)

    write(error_unit, *) "258 = ", two_hundred_and_fifty_eight

    two_pi = double_double(dble(pi))
    write(error_unit, *) "2pi = ", two_pi

    eighty_six_d = double_float(float(forty_three))
    write(error_unit, *) "2pi = ", eighty_six_d

    write(error_unit, *) "int(pi) = ", int(pi)
    write(error_unit, *) "float(forty_three) = ", float(forty_three)
    write(error_unit, *) "float(forty_three) = ", real(forty_three, kind=C_DOUBLE)
    ! Error Passing non-variable expression in variable definition context
    !       (actual argument to INTENT = OUT/INOUT)
    !       >>> Safe to use int(x,kind=Y) as the argument of a function because
    !           the compiler won't let us do it if it's to an OUT/INOUT arg
    ! ier = double_in_place(int(forty_three, kind=C_LONG))

end program 
