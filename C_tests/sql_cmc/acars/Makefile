trg = dbinterface.out
src = main.c

LDLIBS = -lsqlite3 -lpthread -ldl
CFLAGS = -Wall -std=c99

all:$(trg)

$(trg):$(src)
	gcc $(CFLAGS) -o $@ $^ $(LDLIBS)
asm_file=$(src:.c=.s)
asm:$(asm_file)

%.s:%.c
	gcc $(CFLAGS) -g -o $@ -S $<

test:$(trg)
	./$(trg)

clean:
	$(RM) $(trg)
	$(RM) $(asm_file)
