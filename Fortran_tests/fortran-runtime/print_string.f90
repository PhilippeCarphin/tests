module phil_io
    use iso_c_binding

    contains
        subroutine print_string(str, len) bind(C, name="print_string")
            use iso_fortran_env

            integer(C_LONG_LONG) :: len
            character :: str(len)

            write(output_unit, *) str

        end subroutine

end module
