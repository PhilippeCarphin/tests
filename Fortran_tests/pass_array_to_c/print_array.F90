module cprintarray
    use iso_c_binding
    implicit none

    interface
        ! https://www.cenapad.unicamp.br/parque/manuais/Xlf/UG78.HTM#HDRHU00906
        ! Where necessary, the Fortran program constructs a temporary array and
        ! copies all the elements into contiguous storage.  In all cases, the C
        ! routine needs to account for the column-major layout of the array.

        ! Any array section or noncontiguous array is passed as the address of a
        ! contiguous temporary unless an explicit interface exists where the
        ! corresponding dummy argument is declared as an assumed-shape array or
        ! a pointer. To avoid the creation of array descriptors (which are not
        ! supported for interlanguage calls) when calling non-Fortran procedures
        ! with array arguments, either do not give the non-Fortran procedures
        ! any explicit interface, or do not declare the corresponding dummy
        ! arguments as assumed-shape or pointers in the interface:
        subroutine cprint_array_2d_memory(array, ni, nj) bind(C, name="cprint_array_2d_memory")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: ni, nj
        end subroutine

        subroutine cprint_array_2d_indexing(array, ni, nj) bind(C, name="cprint_array_2d_indexing")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: ni, nj
        end subroutine

        subroutine cprint_array_2d_array_yuck(ni, nj, array) bind(C, name="cprint_array_2d_array_yuck")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: ni, nj
        end subroutine

        subroutine cprint_array_1d(array, n) bind(C, name="cprint_array_1d")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: n
        end subroutine
    end interface


    interface fprint_array
        module procedure fprint_array_1d
        module procedure fprint_array_2d
    end interface

    contains
        subroutine fprint_array_1d(array)
            use iso_c_binding
            use iso_fortran_env
            real(C_FLOAT), intent(in), dimension(:) :: array
            write(error_unit,*) "fprint_array_1d(): Fortran adapter for cprint_array_1d"
            write(error_unit,*) "Shape of array: ", shape(array)
            call cprint_array_1d(array, size(array,1))
        end subroutine
        subroutine fprint_array_2d(array)
            use iso_c_binding
            use iso_fortran_env
            real(C_FLOAT), intent(in), dimension(:,:) :: array
            write(error_unit,*) "fprint_array_2d(): Fortran adapter for cprint_array_2d_memory"
            write(error_unit,*) "Shape of array: ", shape(array)
            call cprint_array_2d_memory(array, size(array,1), size(array,2))
        end subroutine

end module
