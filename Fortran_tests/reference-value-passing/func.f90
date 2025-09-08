
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
END MODULE
