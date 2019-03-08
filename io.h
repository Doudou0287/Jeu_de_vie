/**
 * \file io.h
 * \brief fonctions pour l'affichage
 * \author sundus ALKEBSI
 */






#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
* \breif affichage d'une grille
* \param int c un entier
*/  
void affiche_grille (const grille *g);

/**
* \breif effacement d'une grille
* \param g une grille
* \ return \c void
*/
void efface_grille (const grille *g);



/** debute le jeu
* \param *g une grille
* \param *gc une grille
* \ return \c void
*/
void debut_jeu(grille *g, grille *gc);

#endif

