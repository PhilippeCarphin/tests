program main

    use grid

    integer :: ierr
    character(C_CHAR), dimension(14) :: id
    TYPE(TTile) :: t
    TYPE(TGrid) :: g

    t%I0 = 1
    t%I1 = 2
    t%J0 = 1336
    t%J1 = 42
    t%HI = 1
    t%HJ = 1

    ! ierr = c_print_tile(t)

    g%NI = 1000
    g%NJ = 2000
    g%NK = 8

    g%HI = 1
    g%HJ = 2

    g%NbTiles = 1
    ierr = allocate_tiles(g, 1)
    ierr = set_tile(g, 0, t)
    id = "sbonjourlllll"
    g%Id(:) = "sbonjour"//achar(0)

    ierr = c_print_grid(g)

end program
