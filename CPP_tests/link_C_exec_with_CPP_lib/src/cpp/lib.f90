module f
    use iso_c_binding
    contains
        function say_hello_f() bind(C, name="say_hello_f")
            use, intrinsic :: iso_fortran_env
            write(output_unit,'(a)') "Hello from this fortran function"
        end function
end module
