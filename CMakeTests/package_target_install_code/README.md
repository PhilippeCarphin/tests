# Execute code at install and package time

This is a way to get code to run when `make package` or `make install` are run.

The specific task was to generate a file using `configure_file` at the moment
of installing or packaging.

## Mechanics

`make package` wraps `make install`:  When we run `make package`, what happens
is a `make install` but with a different install prefix to generate a package
directory, then some other stuff happens with that like making a `.tar` file.

Because of this, any code that is made to run at install time will also be run
when we do `make package`.

## Landmine

Because `make package` runs an install with a different `CMAKE_INSTALL_PREFIX`
we must take care that any commands that would contain
`${CMAKE_INSTALL_PREFIX}` have `\${CMAKE_INSTALL_PREFIX}` instead.

This is because `install(...)` commands add code to the file
`cmake_install.cmake`.  Suppose we run `cmake ..
-DCMAKE_INSTALL_PREFIX=/some/path/install-dir`, then
```
install(CODE "execute_process(COMMAND touch ${CMAKE_INSTALL_PREFIX}/file")
```
will cause `cmake_install.cmake` to contain the code
```
execute_process(COMMAND touch /some/path/install-dir/file)
```

This is a problem for packaging because when we run `make package`, the file
`cmake_install.cmake` gets executed with a different value of `CMAKE_INSTALL_PREFIX`
but at this point, the path `/some/path/install-dir/file` is hardcoded.

Our package made with `make package` will not contain `file`.

Our initial `install(CODE` command needs to be
```
install(CODE "execute_process(COMMAND touch \${CMAKE_INSTALL_PREFIX}/file")
```
and with that form, we can inspect `cmake_install.cmake and see that it will contain
```
execute_process(COMMAND touch ${CMAKE_INSTALL_PREFIX}/file)
```
