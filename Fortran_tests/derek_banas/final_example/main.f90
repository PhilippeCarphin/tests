program fortrantut
    use shape_mod
    use triangle_mod
    implicit none


    type(triangle_m) :: tri
    tri%x = 10
    tri%y = 20

    print "(a3, f5.2)", "x: ", tri%x
    print "(a3, f5.2)", "y: ", tri%y
    print "(a3, f6.2)", "y: ", tri%get_area()

end program fortrantut
