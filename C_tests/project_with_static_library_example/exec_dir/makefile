################################################################################
# Variables donnant la structure de notre projet
################################################################################
trg=exec
src_dir=./src
build_dir=./build
inc_dir=./include
lib_root = ../ma_lib
lib_name = ma_lib
lib_inc = $(lib_root)/include
src = $(wildcard $(src_dir)/*.c)
################################################################################
# Variables pour les commandes qu'on va exécuter
################################################################################
LD = gcc
CFLAGS += -I $(lib_inc) -I $(inc_dir)
LDFLAGS = -L $(lib_root)/lib -l $(lib_name)
################################################################################
# Variable pour le fichier de notre librairie, normalement on en a pas besoin
################################################################################
lib_file = $(lib_root)/lib/lib$(lib_name).a # 1
################################################################################
# les cibles pour builder notre projet
################################################################################
obj_tmp = $(src:.c=.o)
obj = $(subst $(src_dir), $(build_dir), $(obj_tmp))
abc = $($(subst $(src_dir), $(build_dir), $(obj_tmp)):.c=.o)
bca = $(subst $(src_dir), $(build_dir), $(srd:.c=.o))

.PHONY:vars lib clean_lib clean cleanall
all: $(trg)
$(trg): $(lib_file) $(obj) # 2
	@$(c_yellow); echo "Building executable $@ from $(obj), linking with lib$(lib_name).a"; $(c_none)
	$(LD) -o $(trg) $(obj) $(LDFLAGS)
clean:
	$(RM) exec $(obj)
	$(RM) $(build_dir)/*.d
################################################################################
# Partie non standard
################################################################################
lib:$(lib_file) #4 juste pour pouvoir ecrire 'make lib' dans le terminal
$(lib_file): # 0
	@$(c_green); echo "building library"; $(c_none)
	@cd $(lib_root) ; $(MAKE)
	@$(c_green); echo "done building library"; $(c_none)
cleanall:clean_lib clean
clean_lib:
	@$(c_green); echo "Cleaning library"; $(c_none)
	@cd $(lib_root) ; $(MAKE) clean #3
	@$(c_green); echo "done cleaning library"; $(c_none)
vars:
	@echo "obj = $(obj)"
	@echo "abc = $(abc)"
	@echo "cba = $(cba)"
	@echo "src = $(src)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@cd $(lib_root) ; $(MAKE) vars

-include ../makefile.common
-include *.d

# 0) Normalement un projet qui utilise une librairie externe ne s'occuppe pas de
# builder cette librairie
#
# 1) Pour la raison 0), la variable lib_file est non-standard
#
# 2) Exec ne devrait pas dépendre de la librairie dans un projet standard
#
# 3) On ne s'occupe pas de cleaner la librairie dans un projet dtandard
