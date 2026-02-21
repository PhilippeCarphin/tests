program good
      use, intrinsic :: iso_c_binding
      use, intrinsic :: iso_fortran_env
      implicit none

      ! https://stackoverflow.com/a/46004398/5795941
      write(error_unit, '(a)', advance="no") "The line does not end here, "
      write(error_unit, '(a)') "it ends here>"

end program
