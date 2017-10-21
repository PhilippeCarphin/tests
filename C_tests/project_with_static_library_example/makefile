################################################################################
# Variables donnant la structure de notre projet
################################################################################
trg=exec
lib_root = ma_lib
lib_name = ma_lib
lib_inc = $(lib_root)/include
src = $(wildcard *.c)
################################################################################
# Variables pour les commandes qu'on va exécuter
################################################################################
CC = gcc
LD = gcc
MAKE = make
RM = rm -rf
CFLAGS = -I $(lib_inc) -MMD
LDFLAGS = -L $(lib_root)/lib -l $(lib_name)
################################################################################
# Variable pour le fichier de notre librairie, normalement on en a pas besoin
################################################################################
lib_file = $(lib_root)/lib/lib$(lib_name).a # 1
################################################################################
# Color codes for terminal output
################################################################################
c_green=\033[0;32m
c_magenta=\033[0;35m
c_yellow=\033[0;33m
c_none=\033[0m
################################################################################
# les cibles pour builder notre projet
################################################################################
obj = $(src:.c=.o)
.PHONY:vars lib clean_lib clean cleanall
all: $(trg)
$(trg): $(lib_file) $(obj) # 2
	@echo "$(c_yellow)Building executable $@ from $^$(c_none)"
	$(LD) $(LDFLAGS) -o $(trg) $(obj)
.c.o:
	@echo "$(c_magenta)Building object $@ from $<$(c_none)"
	$(CC) $(CFLAGS) -c $< -o $@
lib:$(lib_file) #4 juste pour pouvoir ecrire 'make lib' dans le terminal
$(lib_file): # 0
	@echo "$(c_green)building library$(c_none)"
	@cd $(lib_root) ; $(MAKE)
	@echo "$(c_green)done building library$(c_none)"
vars:
	@echo "obj = $(obj)"
	@echo "src = $(src)"
cleanall:clean_lib clean
clean_lib:
	@echo "$(c_green)Cleaning library$(c_none)"
	@cd $(lib_root) ; $(MAKE) clean #3
	@echo "$(c_green)done cleaning library$(c_none)"
clean:
	$(RM) exec $(obj)

include *.d

# 0) Normalement un projet qui utilise une librairie externe ne s'occuppe pas de
# builder cette librairie
#
# 1) Pour la raison 0), la variable lib_file est non-standard
#
# 2) Exec ne devrait pas dépendre de la librairie dans un projet standard
#
# 3) On ne s'occupe pas de cleaner la librairie dans un projet dtandard
