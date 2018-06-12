.PHONY :test
asm_files = main.s
c_files =

obj = $(asm_files:.s=.o) $(c_files:.c=.o)


test:a.out
	@./a.out || true # so that a.out's return value doesn't get make to raise an error
a.out:$(obj)
	gcc -o $@ $(obj)

asm:main.s
%.o:%.s
	gcc -c -o $@ $<
vars:
	@echo "obj = $(obj)"
clean:
	$(RM) *.out
	$(RM) *.o
