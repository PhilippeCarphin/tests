PROGRAM main

    integer :: a

    a = truth()

    write (*,*) "a = ", a

    contains

        function truth() result(t)
            use iso_fortran_env
            integer(kind=int64) :: t
            t = 42
        end function
end PROGRAM
