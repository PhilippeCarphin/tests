!
! On my Mac Mini (M1 chip), this program hangs under certain conditions
! If I remove the write in program_module_func(), the program does not
! hang but hangs otherwise.
!
! I have tried it on the linux computers at work and it never hangs.
!
module mainmod
    contains
        real function program_module_func()
            write (*,*) "program_module_func() called"
            program_module_func = 3.1415
        end function
end module

program addNumbers
      use mainmod
      write (*,*) "pi = ", program_module_func()
end program
