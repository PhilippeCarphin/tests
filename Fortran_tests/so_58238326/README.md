
Answering [this stack overflow question](https://stackoverflow.com/questions/58238326/linker-error-when-c-executable-links-in-fortran-library-and-main-in-c-librar)

This code builds, links, and runs successfully without any warnings.

Some notes
- By using `iso_c_binding` and making fortfunc be bind(C), we don't need this:
  ```cmake
  target_compile_options(FortLib PRIVATE /names:lowercase /assume:underscore /iface:cref)
  ```
  I don't have a Windows machine to try this on but this looks the same as what
  people did before we got ISO C bindings to standardize the symbol names used.

- CMake is aware that we are building a static Fortran library.  It is a usage
  requirement that executables that use this library link with `-lgfortrah
  -lquadmath`.  I noticed `libifcoremdd.lib` in the question which points to
  the OP using the Intel compiler.

- I added a header file `fort.h` with `extern "C" {...}` controlled by some
  `#ifdef`'s.  That doesn't change anything compared to having the declarations
  in `.cpp` files.
