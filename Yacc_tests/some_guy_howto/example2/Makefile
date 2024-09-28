all: main

main: lex.yy.c
	$(CC) $< -o $@ -ll

lex.yy.c: example2.l
	lex $<

test: main
	printf "1234asdf\n12\n23\nasdf;xyz;1234" | ./main

clean:
	rm -f main lex.yy.c
