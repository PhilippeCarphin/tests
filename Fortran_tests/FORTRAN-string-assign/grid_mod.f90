module grid_mod
    use tgrid_mod


    use, intrinsic :: iso_c_binding
    implicit none
    interface

        integer(C_INT) FUNCTION grid_print(c_grid_ptr) BIND(C, name="Grid_print")
            use tgrid_mod
            use, intrinsic :: iso_c_binding
            implicit none
            TYPE(TGrid) :: c_grid_ptr
        END FUNCTION
    end interface

end module
