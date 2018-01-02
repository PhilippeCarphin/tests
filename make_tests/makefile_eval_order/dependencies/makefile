
src = a.c b.c

#
# La liste de fichiers .o ne contient pas c.o
#
objects = a.o b.o

trg = a.out

all:$(trg)

#
# Make évalue la dépendance et enregistre que
# $(trg) dépend a.o et de b.o
#
$(trg):$(objects)
	@echo "'building' $@ from $^"
	@echo " ===> Dependency = $^ and objects = $(objects) <==="
	@touch $(trg)

a.o:a.c c.h
	@echo "'building' $@ from $^"
	@touch $@

.c.o:
	@echo "'building' $@ from $^"
	@touch $@

#
# On ajoute c.o à la liste d'objets mais la dépendance pour $(trg) a déjà étée
# évaluée durant le parsing du makefile.
#
objects += c.o

clean:
	rm -rf *.o $(trg)

# Une fois que le makefile au complet a été lu par make, make commence à faire
# le build.  Si j'ai fait
# 	$ make all
# alors make regarde de quoi all dépend.  All dépend de a.out, donc on doit
# builder a.out.  Le fichier a.out dépend de a.o et b.o.  On build donc a.o et
# b.o, ensuite on peut builder a.out.  Quand on a buildé a.out, on peut builder
# all, mais en fait on a déjà fini.

