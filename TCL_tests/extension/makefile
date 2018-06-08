trg=libhello.so
src=sayhello.c

# Locations for the CMC filesystem
tcl_inc=/usr/include/tcl8.6/
tcl_lib=/usr/lib/x86_64-linux-gnu/

LDLIBS=-L$(tcl_lib) -l tclstub8.6
CFLAGS=-shared -DUSE_TCL_STUBS -fPIC -std=c11

$(trg):$(src)
	gcc $(CFLAGS) -o $@ -I$(tcl_inc) $^ $(LDLIBS)

mac:$(src)
	gcc -dynamiclib -DUSE_TCL_STUBS sayhello.c -L/Library/Frameworks/Tcl.framework -ltclstub8.5 -o libhello.dylib
