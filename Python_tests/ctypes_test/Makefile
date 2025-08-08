
src = $(wildcard *.c)
obj = $(src:.c=.o)
lib = libtest.so
CFLAGS += -fpic

%.o:%.c
	gcc -c -fPIC -o $@ $<

$(lib):$(obj)
	gcc -shared $(CFLAGS) $^ -o $@

.PHONY: struct print bool byref
struct:$(lib)
	@printf "\033[35mLD_LIBRARY_PATH=\${PWD}:\${LD_LIBRARY_PATH} python3 -u demo_mystruct.py\033[0m\n"
	@LD_LIBRARY_PATH=${PWD}:${LD_LIBRARY_PATH} python3 -u demo_mystruct.py
print:$(lib)
	@printf "\033[35mLD_LIBRARY_PATH=\${PWD}:\${LD_LIBRARY_PATH} python3 -u demo_print_string_list.py\033[0m\n"
	@LD_LIBRARY_PATH=${PWD}:${LD_LIBRARY_PATH} python3 demo_print_string_list.py
bool:$(lib)
	@printf "\033[35mLD_LIBRARY_PATH=\${PWD}:\${LD_LIBRARY_PATH} python3 -u demo_bool_conversion.py\033[0m\n"
	@LD_LIBRARY_PATH=${PWD}:${LD_LIBRARY_PATH} python3 -u demo_bool_conversion.py
byref:$(lib)
	@printf "\033[35mLD_LIBRARY_PATH=\${PWD}:\${LD_LIBRARY_PATH} python3 -u demo_byref.py\033[0m\n"
	@LD_LIBRARY_PATH=${PWD}:${LD_LIBRARY_PATH} python3 -u demo_byref.py
float:$(lib)
	@printf "\033[35mLD_LIBRARY_PATH=\${PWD}:\${LD_LIBRARY_PATH} python3 -u float.py\033[0m\n"
	@LD_LIBRARY_PATH=${PWD}:${LD_LIBRARY_PATH} python3 float.py
array:$(lib)
	@printf "\033[35mLD_LIBRARY_PATH=\${PWD}:\${LD_LIBRARY_PATH} python3 -u array.py\033[0m\n"
	@LD_LIBRARY_PATH=${PWD}:${LD_LIBRARY_PATH} python3 array.py

test: struct print bool

clean:
	rm -f $(lib) *.o

vars:
	@echo "src = '$(src)'"
	@echo "obj = '$(obj)'"
