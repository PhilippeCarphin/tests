
src = print_string_list.c
lib = libprintlist.so
CFLAGS += -fpic

$(lib):$(src)
	gcc -shared $(CFLAGS) $< -o $@

test:$(lib)
	LD_LIBRARY_PATH=${PWD}:${LD_LIBRARY_PATH} python3 demo_print_string_list.py

clean:
	rm $(lib)
