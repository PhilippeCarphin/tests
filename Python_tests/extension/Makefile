src=myModule.c
obj=myModule.o
lib=myModule.so

LDFLAGS +=-shared
LDLIBS  +=
CFLAGS  += -I /usr/include/python3.5m

all:
	$(CC) $(CFLAGS)

lib:$(lib)
$(lib):$(src)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(LDLIBS)

# FROM TCL EXTENSION for reference
mac:$(src)
	gcc -dynamiclib -DUSE_TCL_STUBS sayhello.c -L/Library/Frameworks/Tcl.framework -ltclstub8.5 -o libhello.dylib
