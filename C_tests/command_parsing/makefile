

EXEC=cmd_parse.out
TEST_ARGS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)

$(EXEC):$(OBJ)
	gcc -o $@ $(OBJ)

test:$(EXEC)
	./$(EXEC) $(TEST_ARGS)

.PHONY:show_vars clean

clean:
	rm -rf *.o
	rm -rf $(EXEC)

show_vars:
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"

