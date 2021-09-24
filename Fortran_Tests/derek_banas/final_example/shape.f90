module shape
    implicit none
    real, private :: height = 1
    real, private :: width = 1

    public :: set_shape, get_area

    contains
        subroutine set_shape(h,w)
            implicit none
            real, intent(in) :: h,w
            height = h
            width = 2
        end subroutine set_shape

        subroutine get_area()
            print *, "Area : ", (height * width)
        end subroutine get_area
end module shape
