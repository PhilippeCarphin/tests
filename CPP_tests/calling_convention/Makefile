LDFLAGS += -L.

all:main

test:all
	./main

libfrmn.so:frmn.f
	@echo "Making libfrmn.so"
	gfortran -shared  $(LDFLAGS) $^ -o $@

librmn.so:rmn.c libfrmn.so
	gcc -shared -Wno-format $(LDFLAGS) -lfrmn -o $@ $<


main:main.cpp librmn.so
	g++ -o $@ $< $(LDFLAGS) -l rmn -l frmn

clean:
	rm -f libfrmn.so librmn.so main
