module maybe_in_maybe_out_mod

interface
    integer function maybe_in_maybe_out(num, b,c) bind(C, name="maybe_in_maybe_out")
        integer :: iun
        integer, intent(in), value :: b,c
    end function
end interface

end module


