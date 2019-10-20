src=myModule.c
obj=myModule.o
lib=myModule.so
mac_lib = libmyModule.dylib


LDFLAGS +=-shared -L /Library/Frameworks/Python.framework/Versions/3.7/lib
LDLIBS  +=
CFLAGS  += -I /Library/Frameworks/Python.framework/Versions/3.7/include/python3.7m

all: lib

lib:$(lib)
$(lib):$(src)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(LDLIBS)

# FROM TCL EXTENSION for reference
mac:$(mac_lib)

$(mac_lib):$(src)
	gcc -dynamiclib -DUSE_TCL_STUBS $< $(CFLAGS) $(LDFLAGS) -ltclstub8.5 -o $@
