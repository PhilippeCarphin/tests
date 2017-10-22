-include ../makefile.common
###############################################################################
# These variables specify your project structure
# lib_name : name of library (the file will be lib$(lib_name).a
# src_dir : directory containing your sources
# include : directory containg the header files of the library
# build_dir : directory containing the intermediate build files
# lib_dir : directory containing the library
###############################################################################
lib_name=ma_lib
src_dir=./src
include_dir=./include
build_dir=./build
lib_dir=lib
ARFLAGS = -crs
CFLAGS += -I $(include_dir) -MMD
################################################################################
# Intermediate variables
################################################################################
src = $(wildcard $(src_dir)/*.c)
inc = -I $(include_dir)
dep = $(wildcard $(build_dir)/*.d)
obj_tmp = $(subst $(src_dir), $(build_dir), $(src))
obj= $(obj_tmp:.c=.o)
trg = $(lib_dir)/lib$(lib_name).a

.PHONY:all vars clean
all:$(trg)
$(trg):$(obj)
	$(c_yellow); echo "Building archive file"; $(c_none)
	$(AR) $(ARFLAGS) $(trg) $(obj)
$(obj): $(build_dir)/%.o : $(src_dir)/%.c
	@$(c_magenta); echo "Building object $@ from $<"; $(c_none)
	@$(CC) $(CFLAGS) -c $< -o $@
vars:
	@echo "src = $(src)"
	@echo "inc = $(inc)"
	@echo "obj = $(obj)"
clean:
	rm -rf $(obj)
	rm -rf $(trg)
	rm -rf $(build_dir)/*.d

-include *.d

