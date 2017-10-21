lib_root = ma_lib

src = $(wildcard *.c)
inc = -I ./$(lib_root)/include
obj = main.o
lib = -L $(lib_root)/lib -l ma_lib

.c.o:
	gcc -c $^ $(inc)

all: exec

exec: $(obj) lib
	gcc -o exec $(obj) $(lib)

lib:
	@echo "building library"
	@cd $(lib_root) ; make
	@echo "done building library"

clean:
	rm -rf exec
	rm -rf *.o
	cd $(lib_root) ; make clean
