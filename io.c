/**
 * \file io.c
 * \brief code pour l'affichage
 * \author sundus ALKEBSI
 */



#include "io.h"

static void affiche_trait(int c) {
  int i;
  for (i = 0; i < c; ++i)
    printf("|---");
  printf("|\n");
  return;
}

static void affiche_ligne(int ligne, const grille *g) {
  for (int i = 0; i < g->nbc; ++i) {
    if (est_vivante(ligne, i, *g))
      printf("| O ");
    else
      printf("|   ");
  }
  printf("|\n");
  return;
}

void affiche_grille(const grille *g) {
  printf("\n");
  affiche_trait(g->nbc);
  for (int i = 0; i < g->nbl; ++i) {
    affiche_ligne(i, g);
    affiche_trait(g->nbc);
  }
  printf("\n");
  return;
}

void efface_grille(const grille *g) { printf("\n\e[%dA", g->nbl * 2 + 5); }






int (*compte_voisins_vivants) (int,int,grille)=compte_voisins_vivants_c;
void debut_jeu(grille *g, grille *gc) {
  int c = getchar();
   int t=0;
  while (c != 'q') { // touche 'q' pour quitter
    switch (c) {
    case '\n': { // touche "entree" pour évoluer
      evolue(g, gc);
      efface_grille(g);
      affiche_grille(g);
      t++;
      printf("\e[2K");
      printf("%d\t",t);

      break;
    }
    case 'n' :
    {
	char nom[50];
	printf("entrez le nom de grille\n");
	scanf("%s",nom);
	init_grille_from_file(nom,g);
	alloue_grille((g->nbl),(g->nbc),gc);
	t=0;
	break;
	} 
    case 'c' :
	{
	if(compte_voisins_vivants==compte_voisins_vivants_c){
			compte_voisins_vivants=compte_voisins_v_n_c;
	}
	else {
		compte_voisins_vivants=compte_voisins_vivants_c;
	  }
	
	break;
	}

    default: { // touche non traitée
      printf("\n\e[1A");
      break;
    }
    }
    c = getchar();
  }
  return;
}

