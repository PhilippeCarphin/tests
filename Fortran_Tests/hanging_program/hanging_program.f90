!
! On my Mac Mini (M1 chip), this program hangs under certain conditions
! If I remove the write in program_module_func(), the program does not
! hang but hangs otherwise.
!
! I have tried it on the linux computers at work and it never hangs.
!
! The problem, according to a Fortran expert at work is that we are doing
! IO while there is already an IO operation under way.
!
! During the IO operation in the program, we call the function which
! itself contains an IO operation.
!
! Te problem does not happen if in the program we do
! integer :: pi
! pi = program_module_func()
! write (*,*) "pi = ", pi
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
