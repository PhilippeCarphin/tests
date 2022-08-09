program fortrantut
    implicit none
    integer, dimension(1:5) :: a1, a2, a3
    real, dimension(1:50) :: aR1
    integer, dimension(5,5) :: a4
    integer :: n, m, x, y
    integer, dimension(:), allocatable :: a5
    integer :: num_vals = 0
    integer, dimension(1:9) :: a6 = (/ 1,2,3,4,5,6,7,8,9 /)
    integer, dimension(1:3, 1:3) :: a7

    a1(1) = 5
    print "(i1)", a1(1)

    do n = 1,5
        a1(n) = n
        print "(i1)", a1(n)
    end do

    do n = 1,5
        do m = 1,5
            a4(n,m) = n * m
            print "(i1, a1, i1, a3, i2)", n, ",", m, " : ", a4(n,m)
        end do
    end do

    do n = 1,5
        print "(5i3)", ( a4(n,m), m=1,5)
    end do

    print "(i3)", size(a1)
    print "(i3)", size(a4)

    print *, "Enter size of array : "
    read *, num_vals
    print *, "Size entered : "
    print "(i3)", num_vals
    allocate(a5(1:num_vals))

    do n = 1, num_vals
        a5(n) = n * num_vals
        print "(i5)", a5(n)
    end do

end program fortrantut
