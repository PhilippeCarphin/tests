%: %.c
	gcc $(shell pkg-config --libs python3-embed) $(shell pkg-config --cflags python3-embed) $< -o $@

test: call_python
	@printf "\033[1;34mRunning PYTHONPATH=. ./$<\033[0m\n"
	@PYTHONPATH=. ./$<

