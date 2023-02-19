module climbingstats
    use iso_c_binding
    implicit none

    type, bind(C) :: climb
        integer(C_INT) :: id
        integer(C_INT) :: difficulty
    end type

    interface
        subroutine print_climb(c) bind(C, name="print_climb")
            use iso_c_binding
            type, bind(C) :: climb
                integer(C_INT) :: id
                integer(C_INT) :: difficulty
            end type
            type(climb) :: c
        end subroutine
    end interface

end module

