program fortrantut
    implicit none
    type Customer
        character (len=40) :: name
        integer :: age
        real :: balance
    end type Customer

    type(Customer), dimension(5) :: customers
    integer :: n

    type(Customer) :: sally
    sally%name = "Sally Smith"
    sally%age = 34
    sally%balance = 320.45

    customers(1) = sally

    customers(2)%name = "Tom May"
    customers(2)%age = 42
    customers(2)%balance = 420.59

    do n = 1,2
        print *, customers(n)
    end do

end program fortrantut
