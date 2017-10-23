# PROJECT DIRECTORY STRUCTURE
src_dir=./src
build_dir=./build
inc_dir=./include
# PROJECT FILES
src = $(wildcard $(src_dir)/*.c)
obj = $(subst $(src_dir),$(build_dir),$(src:.c=.o))
trg=exec
# PROJECT COMPILATION TOOLS AND SETTINGS
CC = gcc
CFLAGS = -I $(inc_dir) -MMD $(extra_flags)

all: $(trg)
$(trg): $(obj)
	$(CC) -o $(trg) $(obj)
$(obj): $(build_dir)/%.o : $(src_dir)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(trg) $(obj)

vars:
	@echo "src = $(src)"
	@echo "obj = $(obj)"
	@echo "CC  = $(CC)"
	@echo "CFLAGS  = $(CFLAGS)"
.PHONY:vars clean
-include $(build_dir)/*.d
