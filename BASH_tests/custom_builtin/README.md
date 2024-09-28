We need the -I's in the Makefile because the BASH includes either weirdly placed
in system paths, or in some install dir somewhere.

Note that the enable command needs to the prefix to the `_struct`, not the
name.

Note how `WORD_LIST` is a linked list of words from the command line.

I see the print from the `_builtin_load` function but not the one from the
`_builtin_unload` one.

The usage thing seems generic enough that it can be left at the start.  I found
this weird but it is consistent with the other builtins: they return 258 (which
comes out as $?=2) when given the --help argument.
