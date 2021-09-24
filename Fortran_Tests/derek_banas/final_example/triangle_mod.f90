module triangle_mod
    use shape_mod
    implicit none
    type, extends(shape_m), public :: triangle_m
    contains
        procedure :: get_area
    end type triangle_m

    contains
        function get_area(this) result(area)

            class(triangle_m) :: this
            real :: area
            area = .5 * this%x * this%y
        end function get_area

end module triangle_mod
