/** 
* \file grille.c
* \brief  code pour les grilles  
* \author sundus alkebsi
*/ 


#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grille.h"

void alloue_grille(int l, int c, grille *g) { 
	int i,j;
	g->nbl=l;
	g->nbc=c;
	g->cellules=malloc(l*sizeof(int*));
	if(g->cellules==NULL)
	{
		exit(0);
	}

	for( i=0; i<l; i++ )
	{
		g->cellules[i]=malloc(c*sizeof(int));
		if (g->cellules[i]==NULL)
			exit(0);
		for( j=0; j<c; j++)
			set_morte(i,j,*g);	
	}
	

 }

void libere_grille(grille *g) {
	int i;
	for( i=0; i<g->nbl;i++){
	free(g->cellules[i]);
	}
	free(g->cellules);
}

void init_grille_from_file(char const *const filename, grille *const g) {
  FILE *pfile = fopen(filename, "r");
  if (pfile == NULL) {
    fprintf(stderr,
            "Erreur (%s:%d): Lecture du fichier \"%s\" impossible (%s)\n",
            __FILE__, __LINE__ - 4, filename, strerror(errno));
    exit(EXIT_FAILURE);
  }

  int l, c;
  fscanf(pfile, "%d", &l);
  fscanf(pfile, "%d", &c);

  alloue_grille(l, c, g);
	int n;
  int vivantes = 0;
  fscanf(pfile, "%d", &vivantes);
  for ( n = 0; n < vivantes; ++n) {
    fscanf(pfile, "%d", &l);
    fscanf(pfile, "%d", &c);
    set_vivante(l, c, *g);
  }

  fclose(pfile);
  return;
}

void copie_grille(const grille *const gs, grille *const gd) {
	int i,j;
  assert(gs->nbl == gd->nbl && gs->nbc == gd->nbc);
  for (i = 0; i < gs->nbl; ++i)
    for ( j = 0; j < gs->nbc; ++j)
      gd->cellules[i][j] = gs->cellules[i][j];
}




int testEqalite(grille g, grille gc1)
{
	int result = 1,i,j;
	if(g.nbc != gc1.nbc || g.nbl != gc1.nbl)
	{
		result = 0;
	}
	for( i = 0; i<g.nbc && result==1; i++)
	{
		for( j = 0; j<g.nbl && result==1; j++)
		{
			if(g.cellules[j][i] != gc1.cellules[j][i])
			{
				result = 0;
			}
		}
	}
	return result;
}

