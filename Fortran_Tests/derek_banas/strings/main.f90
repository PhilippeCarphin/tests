program fortrantut

    implicit none
    character (len=30) :: my_string = "I'm a string  "
    character (len=30) :: my_other_string = "I'm another string  "
    character (len=32) :: my_final_string

    my_final_string = trim(my_string) // " " // trim(my_other_string)
    print *, my_final_string

    print *, my_final_string(3:10)

    ! Note that the length printed is the size of the array, i.e. 30
    print *, len(my_string)
end program fortrantut
