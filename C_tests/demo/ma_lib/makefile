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

################################################################################
# Intermediate variables
################################################################################
src = $(wildcard $(src_dir)/*.c)
inc = -I $(include_dir)
obj_tmp = $(subst $(src_dir), $(build_dir), $(src))
obj= $(obj_tmp:.c=.o)
trg = $(lib_dir)/lib$(lib_name).a

all:libphil.a

.PHONY:vars clean

vars:
	@echo "src = $(src)"
	@echo "inc = $(inc)"
	@echo "obj = $(obj)"

$(obj): build/%.o: src/%.c
	@echo "compiling $^ to $@"
	gcc -c $^ $(inc) -o $@

libphil.a:$(obj)
	ar -crs lib/libphil.a $(obj)

clean:
	rm -rf $(obj)
	rm -rf $(trg)
