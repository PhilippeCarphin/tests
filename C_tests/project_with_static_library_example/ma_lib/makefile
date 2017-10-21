###############################################################################
# These variables specify your project structure
# lib_name : name of library (the file will be lib$(lib_name).a
# src_dir : directory containing your sources
# include : directory containg the header files of the library
# build_dir : directory containing the intermediate build files
# lib_dir : directory containing the library
###############################################################################
lib_name=ma_lib
src_dir=src
include_dir=./include
build_dir=build
lib_dir=lib

AR = ar
ARFLAGS = -crs
CC = gcc
CFLAGS += -I $(include_dir) -MMD

################################################################################
# Intermediate variables
################################################################################
src = $(wildcard $(src_dir)/*.c)
inc = -I $(include_dir)
obj_tmp = $(subst $(src_dir), $(build_dir), $(src))
obj= $(obj_tmp:.c=.o)
trg = $(lib_dir)/lib$(lib_name).a

all:$(trg)

.PHONY:vars clean

vars:
	@echo "src = $(src)"
	@echo "inc = $(inc)"
	@echo "obj = $(obj)"

$(obj): $(build_dir)/%.o: $(src_dir)/%.c
	@echo "compiling $^ to $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(trg):$(obj)
	$(AR) $(ARFLAGS) $(trg) $(obj)

clean:
	rm -rf $(obj)
	rm -rf $(trg)

include $(build_dir)/*.d

