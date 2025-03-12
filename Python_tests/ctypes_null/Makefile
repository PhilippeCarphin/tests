
libecho.so: echo.c
	gcc -shared -o $@ -fPIC $^

test: libecho.so test.py
	python3 test.py
