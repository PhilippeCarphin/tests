    subroutine say_hello() bind(C, name="say_hello")
      use ISO_FORTRAN_ENV
      write(error_unit, *) "HELLO"
    end subroutine say_hello
