execs = original mine mine_better mine_best

%:%.c
	gcc $(shell pkg-config python3-embed --libs --cflags) $< -o $@

pytest: $(execs)
	PYTHONPATH=. ./original philmodule print_numbers 1 2 3
	PYTHONPATH=. ./mine philmodule print_numbers 1 2 3
	PYTHONPATH=. ./mine_better philmodule print_numbers 1 2 3
	PYTHONPATH=. ./mine_best philmodule print_numbers 1 2 3

clean:
	rm -f $(execs)

