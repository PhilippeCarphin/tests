
MODULE datetime_mod
    use, intrinsic :: iso_c_binding
    CONTAINS
        integer(C_INT) function f_print_two_ints(int_val, int_ref) result(err) bind(C, name="f_print_two_ints")
            use, intrinsic :: iso_c_binding
            use, intrinsic :: iso_fortran_env
            integer(C_INT), intent(in), value :: int_val
            integer(C_LONG), intent(in) :: int_ref

            write(error_unit, *) "int_val: ", int_val
            write(error_unit, *) "int_ref: ", int_ref

        end function
END MODULE
