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

      write(error_unit, '(/a/)') "I wish this would appear between two empty lines"

      write(msg_buf, '(/a/)') "I wish this would appear between two empty lines"
      write(error_unit, *) msg_buf
end program

