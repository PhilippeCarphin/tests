src = $(wildcard *.c)
inc = -I ./include
obj = main.o
libdir = lib
lib = -L $(libdir) -l phil
lib_file = lib/libphil.a


.c.o:
	gcc -c $^ $(inc)

all: exec

exec: $(obj) $(lib_file)
	gcc -o exec $(obj) $(lib)

$(lib_file):
	cd lib ; make

clean:
	rm -rf exec
	rm -rf *.o
