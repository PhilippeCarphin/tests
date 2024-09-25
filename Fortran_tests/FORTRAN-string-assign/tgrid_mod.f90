module tgrid_mod
    use, intrinsic :: iso_c_binding
    implicit none

    TYPE, BIND(C) :: TGrid
        character(kind=C_CHAR)         :: Id(14)
        ! type(C_PTR)                    :: Ref
        integer(C_INT)                 :: NI, NJ, NK
        integer(C_INT)                 :: HI, HJ
        integer(C_INT)                 :: NbTiles
        ! type(C_PTR)                    :: Tiles
    END TYPE

end module
