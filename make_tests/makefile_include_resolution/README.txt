Take a look at the source files 

	main.c
	phil.h
	paul.h

and notice that main.c includes phil.h
and that phil.h includes paul.h


Next look at the makefile, notice the target
main.o that states that main.o only depends
on main.c.

Also notice in the makefile the flag -MMD and
the '-include *.d' which are the key to the
whole thing.


Next run demo.sh and be amazed!  It's a short
script that just runs the operations showing
that it works.  Basically an annotated version
of the experiments that I did to convince
myself that I knew how it worked.


