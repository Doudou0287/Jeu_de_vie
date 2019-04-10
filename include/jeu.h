/** 
* \file jeu.h
* \brief header pour les regles du jeu 
* \author sundus alkebsi
*/ 



#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * \brief modulo modifié pour traiter correctement les bords i=0 et j=0
 * dans le calcul des voisins avec bords cycliques
 * \param i un entier
 * \param m un eniter
 * \return i+m modulo m 
*/
static inline int modulo(int i, int m) {return (i+m)%m;}

/**
 * \brief compte le nombre de voisins vivants de la cellule (i,j)
 * les bords sont cycliques.
 * \relatesalso grille
 * \param i un entier
 * \param j un entier
 * \param g une grille
 * \return int le nombre de voisins vivants cycliques
*/
int compte_voisins_vivants_c (int i, int j, grille g);


/**
 * \brief compte le nombre de voisins vivants de la cellule (i,j)
 * les bords sont non cycliques.
 * \relatesalso grille
 * \param i un entier
 * \param j un entier
 * \param g une grille
 * \return int le nombre de voisins vivants non cycliques
*/
int compte_voisins_v_n_c(int i,int j, grille g);


/**
 *  \brief fait évoluer la grille g d'un pas de temps
 * \relatesalso grille
 * \param *g une grille
 * \param *g une grille
 * \return \c void
*/
void evolue (grille *g, grille *gc,int vieil);


/**
 * \brief un pointeur de fonction compte voisins vivants qui pointe vers le calcul de
voisinage en cours
*/
int (*compte_voisins_vivants) (int,int,grille);

int periode(grille g, int v);


int testOscillant(grille g, int v);

int affichageOscillant(grille g, int v);


#endif

