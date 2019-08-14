LDFLAGS += -L.
all:main
test:all
	./main

libfrmn.so:frmn.f
	gfortran -shared -fPIC $(LDFLAGS) $^ -o $@

librmn.so:rmn.c libfrmn.so
	gcc -shared -Wno-format -fPIC $(LDFLAGS) -lfrmn -o $@ $< -O3

main:main.cpp librmn.so
	g++ -o $@ $< $(LDFLAGS) -l rmn -l frmn

clean:
	rm -f libfrmn.so librmn.so main
