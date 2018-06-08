
test:all
	./main.out
all: main.out

main.out:main.o int_to_string.o
	gcc main.o int_to_string.o -o main.out

asm:
	gcc -S -g -c -o main.ref.s main.c

CFLAGS += -g

clean:
	rm -f *.o
