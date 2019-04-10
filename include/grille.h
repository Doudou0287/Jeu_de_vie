/** 
* \file grille.h
* \brief  fonctions pour les grilles  
* \author sundus alkebsi
*/ 



#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdbool.h>

/**
*typedef struct grille

* \structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
*/
typedef struct {
  int nbl;
  int nbc;
  int **cellules;
} grille;

/* alloue une grille de taille l*c, et initialise toutes les cellules à mortes
* \relatesalso grille
* \param l nombre ligne 
* \param  n nombre colonne
* \param *g une grille 
* \n return \c void
*/

void alloue_grille(int l, int c, grille* g);

/*
* \libère une grille 
*\ param g gillle 
* \ return \c void
*/
void libere_grille(grille* g);

/* alloue et initalise la grille g à partir d'un fichier
*\ relatesalso grille 
*\ param i
*\ param j
*\ param g une grille 
*\ return \c void 
*/
void init_grille_from_file(char const*const filename, grille* g);

/**
 * rend vivante la cellule (i,j) de la grille g
 * \relatesalso grille
 * \param i
 * \param j
 * \param g une grille
 * \return \c void
*/
static inline void set_vivante(int i, int j, grille g) {
  g.cellules[i][j] = 1;
}

/**
 * rend morte la cellule (i,j) de la grille g
 * \relatesalso grille
 * \param i
 * \param j
 * \param g une grille
 * \return \c void
*/
static inline void set_morte(int i, int j, grille g) {
  g.cellules[i][j] = 0;
}

/**
 * rend morte la cellule (i,j) de la grille g
 * \relatesalso grille
 * \param i int
 * \param j int
 * \param g une grille
 * \return \c void
*/ 

static inline bool est_vivante(int i, int j, grille g) {
  return g.cellules[i][j] == 1;
}

/**
 *  recopie gs dans gd (sans allocation)
 * \relatesalso grille
 * \param gs grille
 * \param gd grille
 * \return \c void
*/
void copie_grille(const grille *gs, grille *gd);



static inline void vieills(int i, int j , grille g, int vieil){
	if(vieil==1) g.cellules[i][j]++;
	if(g.cellules[i][j]==9) g.cellules[i][j]=0;
} 

/**
 * \rend la celulles[i][j] -1 de la grille g
 * \param i entier
 * \param j entier
 *\return \c void  
*/
static inline void set_non_viable(int i,int j,grille g)
{
	g.cellules[i][j]=-1;
}


/**
 * \tester si la celulles[i][j] est non viable de la grille g
 * \param g une grille
 * \param i entier
 * \param j entier
 *\return int 1 si elle est non_viable, 0 sinon  
*/
static inline int est_non_viable(int i,int j,grille g){
	if(g.cellules[i][j]==-1)
		return 1;
	else return 0;
}

int testEqalite(grille g, grille gc1);


#endif // __GRILLE_H

