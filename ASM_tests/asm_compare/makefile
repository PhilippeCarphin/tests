file=hello
src_dir=Documents/GitHub/tests/ASM_tests/asm_compare
computer=l4712-11
host=phcarb@$(computer).info.polymtl.ca
file=hello.c
base_name=$(file:.c=)
exec=$(base_name).out
asm=$(base_name)-$(shell uname).s

all:
	gcc $(file) -o $(exec)
	gcc -S $(file) -o $(asm)

linux:$(base_name)-Linux.s
$(base_name)-Linux.s: $(file) makefile
	rsync -t hello.c makefile $(host):$(src_dir)
	ssh $(host) "cd $(src_dir) ; make"
	scp $(host):~/$(src_dir)/$@ $@

vars:
	@echo "file = $(file)"
	@echo "asm = $(asm)"
	@echo "base_name = $(base_name)"
