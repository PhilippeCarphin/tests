# Expand aliases

## In function definitions

From the first part, we can see that the aliases are expanded during the reading
of the function definition.

From the second part we see that no alias expansion happens during the execution
of the function.

The third part demonstrates an example of when that could be weird.  Suppose in
an interactive shell, you have `alias ls='ls --color'` and you see that weird
stuff is happening because of it.  If you `unalias ls`, the weirdness may still
happen because any function using `ls` because the `ls` will have been expanded
to `ls --color` when the function definition was read.  At this point, the code
of the function contains `ls --color` and unaliasing `ls` will not change that.
