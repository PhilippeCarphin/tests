program good
      use, intrinsic :: iso_c_binding
      use, intrinsic :: iso_fortran_env
      implicit none

      interface
          subroutine print_string(str) bind(C, name="print_string")
              use, intrinsic :: iso_c_binding
              implicit none
              character(kind=C_CHAR), dimension(*), intent(in) :: str
          end subroutine
      end interface


      character(len=1024) :: msg_buf

      ! Whether to print to a stream or to a buffer, we should concatenate
      ! some newline characters to our string like this:
      write(error_unit,'(a)') "======"
      write(error_unit,'(a)') new_line('a')//"This should be between two empty lines"//new_line('a')//c_null_char
      write(error_unit,'(a)') "======"

      ! Now there is only one "record" and a scalar character buffer works.
      write(msg_buf,'(a)') new_line('a')//"This should be between two empty lines"//new_line('a')//c_null_char
      write(error_unit,'(a)') "======"
      call print_string(msg_buf)
      write(error_unit,'(a)') "======"

end program

