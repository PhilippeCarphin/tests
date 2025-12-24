Timings

Ajouts 

Iris Multivar

# Résumé

On échange le cubes `atm_busin/atm_busou, ocn_busou/ocn_busin` en un seul
transfert MPI.

Les variables échangées sont identifiées auprès de Iris par une chaîne de caractères
délimitée par des virgules avec les variables vectorielles groupées ensemble et
séparées par un `/`.

Par exemple GEM envoit à NEMO

    TODO

et les variables <TODO> sont deux composantes d'un champ vectoriel.

Lorsque les champs sont envoyés, on envoi `atm_busou` en un seul transfert et
on identifie les variables qu'on envoi de la même façon.

Dans les fonctions `cpl{atm,ocn}_xchng` les boucles sur `ivar = 1,
cpl{atm,ocn}_n_fld{ou/in}` sont replacées par un seul appel à
`iris%model_{share,need}` qui reçoit en argument les mêmes chaînes passées à
`iris%model_{provide,consumes}`.

Bien qu'il soit possible d'envoyer/demander des groupes de variables différents
de ceux qu'on a déclaré à l'initialisation, nous réutilisons la chaîne de
caractères envoyée durant les appels à `iris%model_provide/iris%model_consumes`.

J'ai aussi composé les chaînes de caractères manuellement et ça serait bon de
les composer de façon automatique.

Une autre chose, dans NEMO, les tableaux `atm_busou/atm_busin` sont des tableaux
de doubles donc je les ai changés pour des tableaux de floats.  J'ai fait ceci en
changeant

    TODO



