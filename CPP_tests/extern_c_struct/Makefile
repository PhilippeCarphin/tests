CFLAGS += -MMD -g

all: main

%.o:%.c Makefile
	gcc -c $(CFLAGS) -o $@ $<
%.o:%.cpp Makefile
	g++ -c $(CFLAGS) -o $@ $<

%.s:%.c Makefile
	gcc -S $(CFLAGS) -o $@ $<
%.s:%.cpp Makefile
	g++ -S $(CFLAGS) -o $@ $<

asm: main.s coolstruct.s coolclass.s

main: main.o coolstruct.o coolclass.o
	g++ -o $@ $^

-include *.d

clean:
	rm -f main main.o coolstruct.o
