trg=libhello.so
src=sayhello.c

# Locations for the CMC filesystem
tcl_inc=/usr/include/tcl8.5/
tcl_lib=/usr/lib/x86_64-linux-gnu/

LDLIBS=-L$(tcl_lib) -l tclstub8.5
CFLAGS=-shared -DUSE_TCL_STUBS -fPIC

$(trg):$(src)
	gcc $(CFLAGS) -o $@ -I$(tcl_inc) $^ $(LDLIBS)
