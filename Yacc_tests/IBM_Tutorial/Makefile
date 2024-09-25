all: calc

CFLAGS += -MMD

calc.yy.c: calc.l
	lex -o $@ $^

calc.tab.c: calc.y
	yacc -o $@ $^

calc: main.o calc.tab.o calc.yy.o
	gcc -o $@ $^

clean:
	rm -f calc.yy.c calc.tab.c *.o

-include *.d
