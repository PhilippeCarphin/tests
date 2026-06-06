New:

- I tried 'make' and it didn't work.  Undefined references.

- Noticed Bash provides stuff to include in the makefile

- It's better but still doesn't work because we include "loadables.h"
  which maybe we shouldn't need to include

  > The examples do include "loadables.h" but I think maybe we're
  supposed to have our C file in the same directory as "loadables.h"

- Anyway, I added the -I line with the variable `INC_PLUS`.

=====

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
