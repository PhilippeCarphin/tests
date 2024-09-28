all: main

main: lex.yy.c
	$(CC) $< -o $@ -ll

lex.yy.c: example1.l
	lex $<

test: main
	printf "startstop\nstart;\nstop;asdf" | ./main

clean:
	rm -f main lex.yy.c
