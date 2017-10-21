lib_root = ma_lib
trg=exec

CC = gcc
LD = gcc
MAKE = make
RM = rm -rf
inc = -I ./$(lib_root)/include
CFLAGS = $(inc)
LDFLAGS = -L $(lib_root)/lib -l ma_lib


src = $(wildcard *.c)
obj = $(src:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(trg)

exec: $(obj) lib
	$(LD) $(LDFLAGS) -o $(trg) $(obj)

lib:
	@echo "building library"
	@cd $(lib_root) ; make
	@echo "done building library"

vars:
	@echo "obj = $(obj)"
	@echo "src = $(src)"

clean:
	rm -rf exec
	rm -rf *.o
	cd $(lib_root) ; make clean
