module fortfunc_mod
    use, intrinsic :: iso_c_binding
    contains
        integer function fortfunc() bind(C, name="fortfunc")
            implicit none
            fortfunc = 42
        end function
end module
