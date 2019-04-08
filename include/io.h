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
#include "io.h"
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#define SIZEX 1000
#define SIZEY 1000

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



/** 
 * \brief la fenetre graphique
 * \param *g une grille
 *\param *gc une grille
 * \return 0 pour dire que tout va bien
*/
int graphique(grille *g, grille *gc);


/** 
 * \brief dessine la grille
 * \cairo_surface_t *surface 
 * \param g une grille
 * \return \c void
*/
void paint(cairo_surface_t *surface, grille g);



#endif

