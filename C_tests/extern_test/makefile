SRC= $(wildcard *.c)
OBJ=$(SRC:.c=.o)
TRG=a.out
all: $(TRG)

$(TRG):$(OBJ)
	gcc $(OBJ)
vars:
	@echo "OBJ = $(OBJ)"
	@echo "SRC = $(SRC)"

clean:
	rm -f *.o *.out
