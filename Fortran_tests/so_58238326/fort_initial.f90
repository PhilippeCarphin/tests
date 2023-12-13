use, intrinsic :: iso_c_binding
integer function fortfunc() bind(C, name="fortfunc")
    implicit none
    fortfunc = 42
end function
