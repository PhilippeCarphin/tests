# PROJECT DIRECTORY STRUCTURE
src_dir=./src
build_dir=./build
inc_dir=./include
# PROJECT FILES
src = $(notdir $(wildcard $(src_dir)/*.c))
obj = $(src:.c=.o)
trg=exec
# PROJECT COMPILATION TOOLS AND SETTINGS
CFLAGS = -I $(inc_dir) -MMD $(extra_flags)
OUTPUT_OPTION = -o build/$@
VPATH = ./src:./build
all: $(trg)
$(trg): $(obj)
	$(CC) -o $(trg) $(addprefix $(build_dir)/,$(obj))

clean:
	$(RM) $(trg) $(obj)
	$(RM) $(build_dir)/*.o

vars:
	@echo "src = $(src)"
	@echo "obj = $(obj)"
	@echo "CC  = $(CC)"
	@echo "CFLAGS  = $(CFLAGS)"
.PHONY:vars clean
-include $(build_dir)/*.d
