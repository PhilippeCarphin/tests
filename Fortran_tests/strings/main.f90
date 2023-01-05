PROGRAM send_string
      use, intrinsic :: iso_c_binding
      implicit none

      interface
          subroutine c_print_string(str) bind(C, name="print_string")
              use, intrinsic :: iso_c_binding
              implicit none
              character(kind=C_CHAR), dimension(*), intent(in) :: str
          end subroutine
      end interface


          character(len=50, kind=C_CHAR)          :: string
          character(len=30), pointer :: string_ptr
          integer                    ::       len

          allocate(string_ptr)

          !
          ! Manually putting c_null_char at end of string
          !
          string_ptr="It's the eye of the tiger"
          len = len_trim(string_ptr)
          string_ptr(len+1:len+1) = c_null_char
          call print_string(string_ptr)

          !
          ! Without putting c_null_char we have spaces at the end
          ! from C's point of view.  It seems however that Fortran
          ! does still put a c_null_char at the end automatically
          !
          string_ptr="It's the thrill of the fight"
          call print_string(string_ptr)

          !
          ! This also works though I would have liked it if I didn't
          ! have to repeat the dimension in the assignment. And it
          ! seems that if I get the dimension wrong, I can end up with
          ! the C function printing random characters.
          !
          string(1:50)="Risin' up to the challenge of our rivals"
          call print_string(string)

          !
          ! The main reason for this experimentation is to pass a
          ! a string litteral
          call print_string("And the last known survivor")
          call print_string("Stalks his prey in the night")
          call print_string("And he's watching us all with the EEEYYYYEEEAhh...")
          call print_string("...of the tiger")
          call print_string("chika chika chika PIIINRRRR, PIN PIN PIIIIRRRRR")

          write(*,*) "======================= straight call to C function ==============="
          call c_print_string("It's the eye of the tiger")
          call c_print_string("It's the thrill of the fight")
          call c_print_string("Risin' up to the challenge of our rivals")
          call c_print_string("And the last known survivor"//achar(0))
          call c_print_string("Stalks his prey in the night")
          call c_print_string("And he's watching us all with the EEEYYYYEEEAhh...")
          call c_print_string("...of the tiger")
          call c_print_string("chika chika chika PIIINRRRR, PIN PIN PIIIIRRRRR")

contains
    subroutine print_string(f_string)
        !
        ! From the prints done by the straight C calls to C function,
        ! it is possible that the data for the string literals is
        ! stored in consecutive memory.  Fortran handles this because
        ! it has decriptors
        !
        use, intrinsic :: iso_c_binding
        character(len=*) :: f_string
        character(len=4097) :: c_string
        character, dimension(:), ALLOCATABLE :: ac_string
        integer :: len
        len = len_trim(f_string)
        allocate(ac_string(1:len+1))
        c_string = f_string
        c_string(len+1:len+1) = c_null_char
        ac_string(1:len) = f_string(1:len)
        ac_string(len+1:len+1) = c_null_char
        call c_print_string(c_string)
        call c_print_string(ac_string)
        deallocate(ac_string)
    end subroutine


END PROGRAM


