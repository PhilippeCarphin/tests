
src = print_string_list.c
lib = libprintlist.so

$(lib):$(src)
	gcc -shared $< -o $@

test:$(lib)
	python3 demo_print_string_list.py

clean:
	rm $(lib)
