trg=libglobal_string.dylib
src=global_string.c

# Locations for the CMC filesystem
tcl_inc=/usr/include/tcl8.5/
tcl_lib=/usr/lib/x86_64-linux-gnu/

LDLIBS=-L$(tcl_lib) -l tclstub8.6
CFLAGS=-shared -DUSE_TCL_STUBS -fPIC -std=c11 -g

$(trg):$(src)
	# gcc $(CFLAGS) -o $@ -I$(tcl_inc) $^ $(LDLIBS)
	gcc -dynamiclib -DUSE_TCL_STUBS $^ -L/Library/Frameworks/Tcl.framework -ltclstub8.6 -o $@

clean:
	$(RM) $(trg)
