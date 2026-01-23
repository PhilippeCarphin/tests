
PROGRAM main
    integer :: x

    x = allocate_and_really_deallocate(i)

    contains
        integer function allocate_and_really_deallocate(i) result(ret)
            integer, intent(in) :: i
            integer, dimension(:,:), allocatable :: array
            ret = 0
            write(*,*) "Allocating array"
            allocate(array(i,3*i))
            write(*,*) "Deallocating array"
            deallocate(array)
            write(*,*) "Deallocating again just to be sure ;)"
            deallocate(array)
        end function

END PROGRAM
