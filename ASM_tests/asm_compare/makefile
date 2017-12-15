file=hello
asm_file=$(file)-$(shell uname).s
src_dir=Documents/GitHub/tests/ASM_tests/asm_compare
computer=l4712-02
all:
	gcc $(file).c -o $(file).out
	gcc -S $(file).c -o $(asm_file)

linux:$(file)-Linux.s
$(file)-Linux.s:
	# todo: rsync
	ssh phcarb@$(computer).info.polymtl.ca "cd $(src_dir) ; make"
	scp phcarb@$(computer).info.polymtl.ca:~/$(src_dir)/$@ $@


vars:
	@echo "file = $(file)"
	@echo "asm_file = $(asm_file)"
