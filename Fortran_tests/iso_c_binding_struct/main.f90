program main

    use grid

    integer :: ierr
    integer :: len, i
    character(kind=C_CHAR), dimension(13) :: tmp_id
    character(kind=C_CHAR, len=13) :: tmp_id_2
    TYPE(TTile) :: t
    TYPE(TGrid) :: g

    t%I0 = 1
    t%I1 = 2

    t%J0 = 1336
    t%J1 = 42

    t%HI = 1
    t%HJ = 1

    ierr = c_print_tile(t)

    write(*,*) "=================================="
    g%NI = 1000
    g%NJ = 2000
    g%NK = 8

    g%HI = 1
    g%HJ = 2

    ierr = allocate_tiles(g, 1)
    ierr = set_tile(g, 0, t)

    tmp_id(:) = "Bonjour"
    write(*,*) "tmp_id = ", tmp_id

    tmp_id_2 = "This Grid Id"
    write(*,*) "tmp_id_2 = ", tmp_id_2

    len = len_trim(tmp_id_2)
    do i = 1,len
        g%Id(i:i) = tmp_id_2(i:i)
    enddo
    g%Id(len+1:len+1) = c_null_char

    ierr = c_print_grid(g)


end program
