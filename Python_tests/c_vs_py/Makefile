
main_c: main.c
	gcc -o $@ $<

test-c: main_c
	time ./$<

test-py:
	time ./main.py
