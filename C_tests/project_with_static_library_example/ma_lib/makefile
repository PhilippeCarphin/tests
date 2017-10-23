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
obj = $(subst $(src_dir),$(build_dir),$(src:.c=.o))
trg = $(lib_dir)/lib$(lib_name).a

.PHONY:all vars clean
all:$(trg)
$(trg):$(obj)
	$(call archive_info,$@,$^)
	$(AR) $(ARFLAGS) $(trg) $(obj)
vars:
	@echo "src = $(src)"
	@echo "inc = $(inc)"
	@echo "obj = $(obj)"
	@echo "CFLAGS = $(CFLAGS)"
clean:
	rm -rf $(obj)
	rm -rf $(trg)
	rm -rf $(build_dir)/*.d

-include *.d

-include ../makefile.common
