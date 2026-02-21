
MODULE datetime_mod
    use, intrinsic :: iso_c_binding
    INTERFACE
        integer(C_INT) function c_print_datetime(DateTimeVal, DateTimeRef) bind(C, name="print_datetime")
            use, intrinsic :: iso_c_binding
            integer(C_LONG), intent(in), value :: DateTimeVal
            integer(C_LONG), intent(in) :: DateTimeRef
        end function

    END INTERFACE

    CONTAINS
        integer(C_INT) function f_print_datetime(DateTime) result(err)
            use, intrinsic :: iso_c_binding
            integer(C_LONG), intent(in) :: DateTime

            err = c_print_datetime(DateTime, DateTime)

        end function

        integer(C_INT) function f_print_two_ints(int_val, int_ref) result(err) bind(C, name="f_print_two_ints")
            use, intrinsic :: iso_c_binding
            use, intrinsic :: iso_fortran_env
            integer(C_INT), intent(in), value :: int_val
            integer(C_INT), intent(in) :: int_ref

            write(error_unit, *) "int_val: ", int_val
            write(error_unit, *) "int_ref: ", int_ref

        end function
END MODULE
