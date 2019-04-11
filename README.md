#jeudevie

#####  pour compiler :

> il faut déplacer dans le repertoire où se trouve le makefille

> en mode graphique

	make
> en mode texte
	
	make MODE=TEXTE
 

##### pour executer:

	./bin/main ./grilles/grille*.txt


##### pour les touches clavier

###### en mode texte

> la tocuhe "entrer" pour evoluer la grille.

> la touche 'q' pour quitter.

> la touche 'n' pour entrer une nouvelle grille:

	./grilles/grille*.txt
    
> la touche 'c' pour  activer ou désactiver le voisinage cyclique.

> la touche 'v' pour activer ou désactiver le vieillissement.

> la touche 'o' pour tester si la colonie est oscillant ou non avec sa periode.


###### en mode graphique

> "un clic gauche" pour evoluer la grille.

>  "un clic droit" pour quitter.

> la touche 'n' pour entrer une nouvelle grille:

	./grilles/grille*.txt
    
> la touche 'c' pour  activer ou désactiver le voisinage cyclique.

> la touche 'v' pour activer ou désactiver le vieillissement.

> la touche 'o' pour afficher si la colonie est oscillant ou non avec sa periode.

##### pour génerer la documentation doxygen 

	make doc
    
##### pour supprimer les *.o et le main

	make clean

##### generer une archive
une archive qui contient le code source, Doxyfile et le makefile

	make dist
    

