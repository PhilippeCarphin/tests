# Preprocessing based on filename

This test demonstrates that the filename can affect whether or not files will
be preprocessed.

When the Makefile generator is used, files may or may not be preprocessed based
on the file extension.

However when the Ninja generator is used, files are *always* preprocessed
because Ninja uses the preprocessed files as a means of reliably discovering
module dependencies in Fortran code.

# Preprocessor directives in non-preprocessed files

The Fortran compilers that I have tried simply ignore and print a warning when
compiling files that were not preprocessed.

This is why we may see the print that is encased between `#if 0 ... #endif`
when we run the executable produced by `nopreproc.f90`.  We will never see it
if we use the Ninja generator.
