PROGRAM send_string
      use iso_c_binding

      interface
          subroutine print_string(str) bind(C, name="print_string")
              use iso_c_binding
              type(C_PTR) :: str
          end subroutine
      end interface

          character(len=30), pointer :: filename
          character(len=80)          :: stack_filename
          type(C_PTR)                :: c_filename, c_stack_filename
          integer                    :: len

          !
          ! If we assign a string that is longer than the size of stack_filename
          ! stack_filename will receive the first 30 (its length) characters of
          ! what we assigned and it doesn't cause a segfault
          !
          stack_filename = "/home/phc001/.aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaprofile"

          stack_filename = "/home/phc001/.profile"
          !
          ! If we change the length of the character array from 30 to 80, the
          ! printed "asdf" moves to the right, so the space-padding is still
          ! printed.
          !
          write (*,*) stack_filename, "asdf"
          ! If we assign to filename before calling 'allocate', we cause a segfault
          allocate(filename)
          filename="/home/phc001/.profile"

          !
          ! The following causes a compilation error:
          !      Error: Argument X at (1) to C_LOC shall have either
          !      the POINTER or the TARGET attribute
          !
          ! c_stack_filename = c_loc(stack_filename)
          !

          write (*,*) "MARKER"
          write (*,*) "Fortran filename : ", filename

          len = len_trim(filename)
          write (*,*) "value of len_trim(filename): ", len
          filename(len+1:len+1) = c_null_char
          c_filename = c_loc(filename)

          call print_string(c_filename)

END PROGRAM


