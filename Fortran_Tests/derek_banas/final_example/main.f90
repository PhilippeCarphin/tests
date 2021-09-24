program fortrantut
    use shape_mod
    use triangle_mod
    implicit none


    type(triangle_m) :: tri
    try%x = 10
    try%y = 20

    print "(a3, f5.2)", "x: ", tri.x
    print "(a3, f5.2)", "y: ", tri.y
    print "(a3, f5.2)", "y: ", tri.y

end program fortrantut
