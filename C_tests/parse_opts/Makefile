trg=exec

src_dir=.
build_dir=.
inc_dir=.

src = $(wildcard $(src_dir)/*.c)
obj = $(subst $(src_dir),$(build_dir),$(src:.c=.o))
trg=exec

CFLAGS = -g -Wall -MMD -I $(inc_dir) 

all: test
$(trg): $(obj)
	gcc -o $(trg) $(obj)
$(obj): $(build_dir)/%.o : $(src_dir)/%.c
	gcc $(CFLAGS) -c $< -o $@
clean:
	$(RM) exec $(obj)
vars:
	@echo "src = $(src)"
	@echo "obj = $(obj)"

test: $(trg)
	./$(trg) first_name -p path/to/file -f 2.342


.PHONY:vars clean
-include $(build_dir)/*.d
