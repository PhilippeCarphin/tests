CFLAGS += -O3

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

.PHONY:clean

all:main.out

test:all
	./main.out

main.out:$(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.exe
