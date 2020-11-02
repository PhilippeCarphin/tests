
a.out:external.o main.o
	$(CC) $^ -o $@

test:a.out
	./$<

clean:
	rm -f *.o
	rm -f *.out
