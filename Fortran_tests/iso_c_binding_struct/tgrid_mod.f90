module tgrid_mod

      use, intrinsic :: iso_c_binding
      implicit none

      TYPE, BIND(C) :: TTile
          INTEGER(C_INT) I0, I1
          INTEGER(C_INT) J0, J1
          INTEGER(C_INT) HI, HJ
      END TYPE

      TYPE, BIND(C) :: TGrid
          character(kind=C_CHAR)         :: Id(14)
          integer(C_INT)                 :: NI, NJ, NK
          integer(C_INT)                 :: HI, HJ
          integer(C_INT)                 :: NbTiles
          type(C_PTR)                    :: Tiles
      END TYPE

end module
