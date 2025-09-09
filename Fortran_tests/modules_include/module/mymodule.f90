module my_module

    contains
        integer function hello_world(name)
            character(len=*) :: name
            write(*,"('Hello ',a)") name
            hello_world = 0
            return
        end function
end module
