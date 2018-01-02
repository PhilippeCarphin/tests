
all: main.out

main.out:main.o int_to_string.o
	gcc main.o int_to_string.o -o main.out

CFLAGS += -g

clean:
	rm -f *.o
