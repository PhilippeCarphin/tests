!
! This test demonstrates how optional parameters propagate.
! If 'b' was not passed to first, then the inner call 'second(a,b,c)' behaves
! as if 'b' was not there.
!
program optional
    use, intrinsic :: iso_fortran_env
    use, intrinsic :: iso_c_binding
    implicit none
    call first(5, b=1,c=2)
    call first(6, c=4)
    call first(5, b=1)
    call first(5)
contains

    subroutine first(a,b,c)
        integer a
        integer, optional :: b,c
        call second(a,b=b,c=c)
        return
    end subroutine

    subroutine second(a,b,c)
        integer a
        integer, optional :: b,c
        write(output_unit, '("a="i3,"  present(b)="l1,"  present(c)=",l1)') a, present(b), present(c)
        write(output_unit, '("a="i3 ", b="i3", c="i3)') a,b,c
        return
    end subroutine
end program
