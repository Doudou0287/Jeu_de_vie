#include "jeu.h"

int compte_voisins_vivants(int i, int j, grille g) {
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




void evolue(grille *g, grille *gc) {
  copie_grille(g, gc); // copie temporaire de la grille
  for (int i = 0; i < g->nbl; i++) {
    for (int j = 0; j < g->nbc; ++j) {
      /*set_vivante(i, j, *g);*/
      /*set_morte(i, j, *g);*/
    }
  }
}

