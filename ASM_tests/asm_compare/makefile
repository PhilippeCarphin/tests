file=hello
asm_file=$(file)-$(shell uname).s
all:
	gcc $(file).c -o $(file).out
	gcc -S $(file).c -o $(asm_file)
	ssh phcarb@l3818-01.info.polymtl.ca "cd ~/Documents/GitHub/tests/ASM_tests/asm_compare/ ; make"

vars:
	@echo "file = $(file)"
	@echo "asm_file = $(asm_file)"
