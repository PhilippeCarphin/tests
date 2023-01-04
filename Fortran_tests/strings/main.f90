PROGRAM send_string
      use iso_c_binding

      interface
          subroutine print_string(str) bind(C, name="print_string")
              use iso_c_binding
              character(C_CHAR) :: str(*)
          end subroutine
      end interface

          character(len=50)          :: string
          character(len=30), pointer :: string_ptr
          integer                    :: len

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
          ! I don't understand why but this call prints
          ! C: print_string(): string 'And he's watching us all with the EEEYYYEEE......of the tiger'
          call print_string("And he's watching us all with the EEEYYYYEEE...")

          call print_string("...of the tiger")


END PROGRAM


