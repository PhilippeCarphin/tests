module grid

    use, intrinsic :: iso_c_binding
    use tgrid_mod
    implicit none


    interface
        integer(C_INT) FUNCTION c_print_tile(t) BIND(C, name="print_tile")
            use, intrinsic :: iso_c_binding
            use tgrid_mod
            implicit none
            TYPE(TTILE) :: t
        END FUNCTION
        integer(C_INT) FUNCTION c_print_grid(c_grid_ptr) BIND(C, name="print_grid")
            use, intrinsic :: iso_c_binding
            use tgrid_mod
            implicit none
            TYPE(TGRID) :: c_grid_ptr
        END FUNCTION
        integer(C_INT) FUNCTION allocate_tiles(g, n) BIND(C, name="allocate_tiles")
            use, intrinsic :: iso_c_binding
            use tgrid_mod
            implicit none
            integer(C_INT), value :: n
            TYPE(TGRID) :: g
        end FUNCTION
        integer(C_INT) FUNCTION set_tile(g, i, t) BIND(C, name="set_tile")
            use, intrinsic :: iso_c_binding
            use tgrid_mod
            implicit none
            TYPE(TGRID) :: g
            integer(C_INT), value :: i
            TYPE(TTILE) :: t
        end FUNCTION
    end interface
end module
