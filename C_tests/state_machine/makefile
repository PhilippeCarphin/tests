src = $(wildcard *.c)
obj = $(src:.c=.o)
exec = machine.out

CFLAGS += -g -Wall -Werror=implicit-function-declaration -MMD
LDLIBS += -l pthread

test:$(exec)
	./$(exec)

all:$(exec)

$(exec):$(obj)
	gcc -o $@ $^ $(LDLIBS)
clean:
	$(RM) $(obj) $(exec)
vars:
	@echo "src = $(src)"
	@echo "obj = $(obj)"

-include *.d
