.PHONY :test
asm_files = sum.s add.s
c_files = main.c

obj = $(asm_files:.s=.o) $(c_files:.c=.o)


test:a.out
	@./a.out || true # so that a.out's return value doesn't get make to raise an error
a.out:$(obj)
	gcc -o $@ $(obj)
asm:main.s
main.s:main.c
	gcc -S main.c
main.o:main.c
	gcc -c -o $@ $<
%.o:%.s
	gcc -c -o $@ $<
vars:
	@echo "obj = $(obj)"
clean:
	$(RM) *.out
	$(RM) *.o
