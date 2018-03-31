CFLAGS += -Wall -Wunused-parameter

test:all
	./main.out

all:main.out

main.out:main.o
	gcc $< -o $@

clean:
	rm -f main.out
	rm -f main.o
