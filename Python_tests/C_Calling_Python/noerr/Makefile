%: %.c
	gcc $(shell pkg-config --libs python3-embed) $(shell pkg-config --cflags python3-embed) $< -o $@
test: call_python
	PYTHONPATH=. ./$<

