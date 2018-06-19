
CFLAGS += -Wall -g -std=c99
LDLIBS += -l git2

.PHONY: all a.out
all:a.out

a.out:main.c
	gcc $(CFLAGS) $^ $(LDLIBS)
	./a.out
