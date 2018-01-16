src = $(wildcard *.c)
obj = $(src:.c=.o)
exec = machine.out

CFLAGS += -g -Wall -Werror=implicit-function-declaration
LDLIBS += -l pthread

all:$(exec)

$(exec):$(obj)
	gcc -o $@ $^ $(LDLIBS)

test:$(exec)
	./$(exec)

clean:
	$(RM) $(obj) $(exec)

vars:
	@echo "src = $(src)"
	@echo "obj = $(obj)"
