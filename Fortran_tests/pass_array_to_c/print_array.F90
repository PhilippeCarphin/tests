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
        subroutine cprint_array_2d_memory(array, n_rows, n_cols) bind(C, name="cprint_array_2d_memory")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: n_rows, n_cols
        end subroutine

        subroutine cprint_array_1d_memory(array, n) bind(C, name="cprint_array_1d_memory")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: n
        end subroutine

        subroutine cprint_array_2d_row_major_indexing(array, n_rows, n_cols) bind(C, name="cprint_array_2d_row_major_indexing")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: n_rows, n_cols
        end subroutine

        subroutine cprint_array_2d_column_major_indexing(array, n_rows, n_cols) bind(C, name="cprint_array_2d_column_major_indexing")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: n_rows, n_cols
        end subroutine

        subroutine cprint_array_2d_row_major_forbidden_syntax(n_rows, n_cols, array) bind(C, name="cprint_array_2d_row_major_forbidden_syntax")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: n_rows, n_cols
        end subroutine

        subroutine cprint_array_2d_column_major_forbidden_syntax(n_rows, n_cols, array) bind(C, name="cprint_array_2d_column_major_forbidden_syntax")
            use iso_c_binding
            real(C_FLOAT), intent(in), dimension(*) :: array
            integer(C_INT), intent(in), value       :: n_rows, n_cols
        end subroutine
    end interface


    contains
        subroutine fprint_array_2d_memory(array)
            use iso_c_binding
            use iso_fortran_env
            real(C_FLOAT), intent(in), dimension(:,:) :: array
            write(error_unit,*) "fprint_2d_array_memory(): Fortran adapter for cprint_2d_array_memory()"
            write(error_unit,*) "Shape of array: ", shape(array)
            call cprint_array_2d_memory(array, size(array,1), size(array,2))
        end subroutine
        subroutine fprint_array_1d_memory(array)
            use iso_c_binding
            use iso_fortran_env
            real(C_FLOAT), intent(in), dimension(:) :: array
            write(error_unit,*) "fprint_array_1d_memory(): Fortran adapter for cprint_array_1d_memory()"
            write(error_unit,*) "Shape of array: ", shape(array)
            call cprint_array_1d_memory(array, size(array,1))
        end subroutine
        subroutine fprint_array_2d_row_major_indexing(array)
            use iso_c_binding
            use iso_fortran_env
            real(C_FLOAT), intent(in), dimension(:,:) :: array
            write(error_unit,*) "fprint_array_2d_row_major_indexing(): Fortran adapter for cprint_array_2d_row_major_indexing()"
            write(error_unit,*) "Shape of array: ", shape(array)
            call cprint_array_2d_row_major_indexing(array, size(array,1), size(array,2))
        end subroutine
        subroutine fprint_array_2d_column_major_indexing(array)
            use, intrinsic :: iso_c_binding
            use, intrinsic :: iso_fortran_env
            real(C_FLOAT), intent(in), dimension(:,:) :: array
            write(error_unit,*) "fprint_array_2d_column_major_indexing(): Fortran adapter for cprint_array_2d_column_major_indexing()"
            write(error_unit,*) "Shape of array: ", shape(array)
            call cprint_array_2d_column_major_indexing(array, size(array,1), size(array,2))
        end subroutine
        subroutine fprint_array_2d_column_major_forbidden_syntax(array)
            use, intrinsic :: iso_c_binding
            use, intrinsic :: iso_fortran_env
            real(C_FLOAT), intent(in), dimension(:,:) :: array
            write(error_unit,*) "fprint_array_2d_column_major_forbidden_syntax(): Fortran adapter for cprint_array_2d_column_major_forbidden_syntax()"
            write(error_unit,*) "Shape of array: ", shape(array)
            call cprint_array_2d_column_major_forbidden_syntax(size(array,1), size(array,2), array)
        end subroutine
        subroutine fprint_array_2d_row_major_forbidden_syntax(array)
            use, intrinsic :: iso_c_binding
            use, intrinsic :: iso_fortran_env
            real(C_FLOAT), intent(in), dimension(:,:) :: array
            write(error_unit,*) "fprint_array_2d_row_major_forbidden_syntax(): Fortran adapter for cprint_array_2d_row_major_forbidden_syntax()"
            write(error_unit,*) "Shape of array: ", shape(array)
            call cprint_array_2d_row_major_forbidden_syntax(size(array,1), size(array,2), array)
        end subroutine


end module
