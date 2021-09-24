program fortrantut
    implicit none
    integer, pointer :: p, q

    integer, pointer, dimension(:) :: a_ptr

    integer, target :: my_target

    ! Causes a segfault because p has not been allocated
    ! p = 6

    allocate(p)
    p = 7
    print "(a5,i1)", "p    ", p

    my_target = 7

    q => my_target
    q = q + 2

    print "(a5,i1)", "p    ", p
    print "(a5,i1)", "q    ", q

    ! deallocate(q) causes a crash because it doesn't point to allocated memory
    nullify(q)

    ! nullify(p) would cause the following deallocate to crash the program.
    ! This is different from C where free(NULL) is legal according
    ! to the standard.
    deallocate(p)
    ! deallocate(p) would cause a crash equivalent to
    ! double free corruption in C.

end program fortrantut
