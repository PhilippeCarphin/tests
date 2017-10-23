trg=exec

src_dir=./src
build_dir=./build
inc_dir=./include

src = $(wildcard $(src_dir)/*.c)
obj = $(subst $(src_dir),$(build_dir),$(src:.c=.o))
trg=exec

all: $(trg)
$(trg): $(obj)
	gcc -o $(trg) $(obj)
$(obj): $(build_dir)/%.o : $(src_dir)/%.c
	gcc -I $(inc_dir) -MMD -c $< -o $@
clean:
	$(RM) exec $(obj)
vars:
	@echo "src = $(src)"
	@echo "obj = $(obj)"

.PHONY:vars clean
-include $(build_dir)/*.d
