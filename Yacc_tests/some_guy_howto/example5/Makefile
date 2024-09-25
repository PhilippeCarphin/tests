all: main

lex.yy.c: example5.l y.tab.h
	lex $<

y.tab.h: example5.y
	yacc -d $<

y.tab.c: example5.y
	yacc -d $<

main: y.tab.c lex.yy.c
	$(CC) $^ -o $@

test: main
	cat input.txt | ./main

clean:
	rm -f lex.yy.c y.tab.h y.tab.c main
