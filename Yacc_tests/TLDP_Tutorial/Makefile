heat.c : heat.lex heat.yy.c
	lex -o $@ $<

heat.yy.c : heat.y
	yacc -d -o $@ $<

heat: heat.o heat.yy.o
	gcc -o $@ $^

clean:
	rm -f *.o heat.c heat.yy.c *.h
