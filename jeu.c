/**
 * \file jeu.c
 * \brief code pour le jeu
 * \author sundus ALKEBSI
 */





#include "jeu.h"

int compte_voisins_vivants_c(int i, int j, grille g) {
  int v = 0, l=g.nbl, c=g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
  return v;
}



int compte_voisins_v_n_c(int i,int j, grille g){
	int v=0;
	if(i>0 && j>0)
		v+=est_vivante((i-1),(j-1),g);
	if(i>0 )
		v+=est_vivante((i-1),(j),g);
	if(i>0 && j<(g.nbc-1))
		v+=est_vivante((i-1),(j+1),g);
	if(j>0)
		v+=est_vivante((i),(j-1),g);
	
	if(j<(g.nbc-1))
		v+=est_vivante((i),(j+1),g);
	if(i<(g.nbl-1) && j>0)
		v+=est_vivante((i+1),(j-1),g);
	
	if(i<(g.nbl-1))
		v+=est_vivante((i+1),(j),g);
	
	if(i<(g.nbl-1) && j<(g.nbc-1))
		v+=est_vivante((i+1),(j+1),g);

	return v;
}



void evolue(grille *g, grille *gc) {
  copie_grille(g, gc); // copie temporaire de la grille
	int v;
  for (int i = 0; i < g->nbl; i++) {
    for (int j = 0; j < g->nbc; ++j) {
		v=compte_voisins_vivants (i,j,*gc);
		if(est_vivante(i,j,*g)){
			if(v!=2 && v!=3) set_morte(i,j,*g);
	 	 }
		else{
			if(v==3) set_vivante(i,j,*g);
		 }
		
     
    }
  }
}

