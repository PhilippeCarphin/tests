Ce test montre l'ordre des événements lors d'une commande make.

1) Le makefile est lu du début à la fin.
	Pour chaque ligne, selon la nature de la ligne,
	- Les définitions de variables sont lues.
	- Les dépendances sont lues.  Quand celles-ci sont lues, des variables
	  doivent être évaluées.
	- La règle qui est lue, mais les variables dans ces lignes ne sont pas
	  évaluées.  Ces lignes ne seront évaluées qu'après que tout le makefile ait
	  été lu par make.  À ce moment les variables peuvent avoir des valeurs
	  différentes.

Dans le makefile, on doit porter attention à la variable objects

La dernière ligne du output de make montre que la variable $(objects) vallait
"a.o b.o" lorsque la dépendance a étée enregistrée, mais que la varaible
$(objects) vaut "a.o b.o c.o" lorsque la règle est exécutée car l'évaluation des
varaibles dans une recette est différée au moment de l'exécution de la règle.

Et l'exécution d'une recette n'a lieu qu'après que le makefile ait été 'parsé'
au complet.
