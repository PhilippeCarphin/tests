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

      character(len=1024), dimension(3) :: msg_buf_1d

      ! A '/' can be used in format strings as a way to insert newlines
      ! and it works when we are writing to a file or stdout/stderr
      write(error_unit,'(a)') "Previous message"
      write(error_unit,'(/a/)') "This should be between two empty lines"
      write(error_unit,'(a)') "Next message"

      ! However, it's some kind of "record" thing and the '/a/' format string
      ! seems to actually represent something to be written to three records
      write(msg_buf_1d,'(a/a/a)') "fist", "second", "third"
      write(error_unit, '("msg_buf_1d(1): "a)') trim(msg_buf_1d(1))
      write(error_unit, '("msg_buf_1d(2): "a)') trim(msg_buf_1d(2))
      write(error_unit, '("msg_buf_1d(3): "a)') trim(msg_buf_1d(3))
      ! write(error_unit,*) msg_buf_1d

end program
