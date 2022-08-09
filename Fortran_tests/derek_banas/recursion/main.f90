program fortrantut
    implicit none
    integer :: ans, n

    do n = 1, 10
        print 100, n, factorial(n)
        100 format(' ', i3, 2x, i8)
    end do

    contains
        recursive function factorial(n) result(o)
            integer :: n, o

            if (n == 1) then
                o = 1
            else
                o = n * factorial(n - 1)
            end if

        end function factorial
end program fortrantut
