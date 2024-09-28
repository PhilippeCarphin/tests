all: main

main: lex.yy.c
	$(CC) $< -o $@ -ll

lex.yy.c: example3.l
	lex $<

test: main
	cat example3_input.txt | ./main

clean:
	rm -f main lex.yy.c
