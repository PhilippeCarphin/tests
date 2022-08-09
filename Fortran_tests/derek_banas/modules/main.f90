program fortrantut
    use mult_mod
    implicit none
    integer :: ans, ans2
    real :: r_ans

    print "(a8,i3)", "5 + 4 = ", get_sum(5,4)
    print "(a8,i3)", "5 + 4 = ", get_sum2(5,4)
    print "(a8,i3)", "5 + 4 = ", get_sum3(5,4)
    print "(a8,i3)", "5 + 1 = ", get_sum3(5)

    print "(a8,i3)", "5 * 4 = ", mult(5,4)
    print "(a8,f5.2)", "5 * 4 = ", mult(5.0,4.0)

    contains


        integer function get_sum(n1, n2)
            implicit none
            integer :: n1, n2, sum, other_var

            other_var = 5

            sum = n1 + n2

            ! Returned value seems to be the last value assigned
            ! Uncommenting the `other_var = 7` below changes the returned value
            ! but the line `other_var = 5` does not.
            ! other_var = 7

        end function get_sum

        function get_sum2(n1, n2) result(sum)
            implicit none
            integer, intent(in) :: n1, n2
            integer :: sum, other_var

            sum = n1 + n2

            ! Because the result is declared explicitely, this line
            ! does not change the returned value
            other_var = 7

        end function

        pure function get_sum3(n1, n2) result(sum)
            implicit none
            integer, intent(in) :: n1
            integer, intent(in), optional :: n2
            integer :: sum

            if(present(n2)) then
                sum = n1 + n2
            else
                sum = n1 + 1
            end if

        end function get_sum3

end program fortrantut
