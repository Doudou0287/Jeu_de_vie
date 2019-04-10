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



void evolue(grille *g, grille *gc,int vieil) {
  copie_grille(g, gc); // copie temporaire de la grille
	int v;
	int i,j;
  for ( i = 0; i < g->nbl; i++) {
    for ( j = 0; j < g->nbc; ++j) {
		v=compte_voisins_vivants (i,j,*gc);
		if(est_vivante(i,j,*g)){
			if(v!=2 && v!=3) set_morte(i,j,*g);
			else vieills(i,j,*g,vieil);
	 	 }
		else if(est_non_viable(i,j,*g)==0)
		{
			if(v==3) set_vivante(i,j,*g);
		 }
		
     
    }
  }
  return;
}


int testOscillant(grille g, int v)
{
	int m = 0;
	int result=0;	
	grille gc1, gc2;
	alloue_grille(g.nbl,g.nbc,&gc1);
	alloue_grille(g.nbl,g.nbc,&gc2);
	copie_grille(&g,&gc1);
	copie_grille(&g,&gc2);
	evolue(&gc1,&gc2,v);
	while(testEqalite(g,gc1)==0 && m<100)
	{
		evolue(&gc1,&gc2,v);
		m++;
	}
	if(m==100 || m==0)
	{
		result = 0;
	}
	else
	{
		result = 1;
	}
	libere_grille(&gc1);
	libere_grille(&gc2);
	return result;
}
int periode(grille g, int v)
{
	int m = 1;	
	grille gc1, gc2;
	alloue_grille(g.nbl,g.nbc,&gc1);
	alloue_grille(g.nbl,g.nbc,&gc2);
	copie_grille(&g,&gc1);
	copie_grille(&g,&gc2);
	evolue(&gc1,&gc2,v);
	while(testEqalite(g,gc1)==0 && m<100)
	{
		evolue(&gc1,&gc2,v);
		m++;
	}
	libere_grille(&gc1);
	libere_grille(&gc2);
	return m;
}



int affichageOscillant(grille g, int v)
{
	int m =0;
	int result=0;
	int test=0;
	grille gc1,gc2;
	alloue_grille(g.nbl,g.nbc,&gc1);
	alloue_grille(g.nbl,g.nbc,&gc2);
	copie_grille(&g,&gc1);
	copie_grille(&g,&gc2);
	while (m<100 && result==0)
	{
		result = testOscillant(gc1,v);
		evolue(&gc1,&gc2,v);
		m++;
	}
	if(result==0)
	{
		test=0;
	}
	else if(m != 1)
	{
		test=2;
	}
	else
	{
		test=1;
	}
	libere_grille(&gc1);
	libere_grille(&gc2);
	return test;
}

int delai_Osciller(grille g, int v)
{
	int m =0;
	int result=0;
	grille gc1, gc2;
	alloue_grille(g.nbl,g.nbc,&gc1);
	alloue_grille(g.nbl,g.nbc,&gc2);
	copie_grille(&g,&gc1);
	copie_grille(&g,&gc2);
	while (m<100 && result==0)
	{
		result = testOscillant(gc1,v);
		evolue(&gc1,&gc2,v);
		m++;
	}
	return m-1;
}

