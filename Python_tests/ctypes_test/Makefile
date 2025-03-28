
src = $(wildcard *.c)
obj = $(src:.c=.o)
lib = libtest.so
CFLAGS += -fpic

%.o:%.c
	gcc -c -fPIC -o $@ $<

$(lib):$(obj)
	gcc -shared $(CFLAGS) $^ -o $@

test:$(lib)
	LD_LIBRARY_PATH=${PWD}:${LD_LIBRARY_PATH} python3 demo_print_string_list.py

clean:
	rm -f $(lib) *.o

vars:
	@echo "src = '$(src)'"
	@echo "obj = '$(obj)'"
