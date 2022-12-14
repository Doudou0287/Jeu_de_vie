#include "io.h"

int v=0;
int temps=0;
int (*compte_voisins_vivants) (int,int,grille)=compte_voisins_vivants_c;
void paint(cairo_surface_t *surface, grille g,int v,int o){

	int CSIZE = 52 ;
	char temp[100];
	sprintf(temp,"%d",temps);
	
	
	char age[2];
	age[1]= '\n'; 

	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.5, 0.5, 0.5);
	cairo_paint(cr);
	int i,j;
	// filled rectangle
	for( i=0; i<g.nbl; i++)
	{
		for(j=0; j<g.nbc; j++)
		{	
			cairo_rectangle(cr,j*52+30,i*52+30,50,50);
			if (g.cellules[i][j] == -1)
			{				
				cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
				cairo_fill(cr);
			}
			else if (g.cellules[i][j] == 0)
			{
				cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
				cairo_fill(cr);
			}
			else
			{ 				
				cairo_set_source_rgb (cr, 0.0, 0.0, 1.0);
				cairo_fill(cr);
				
				if(v==1){
				sprintf(age,"%d",g.cellules[i][j]-1);
				cairo_select_font_face(cr,"serif",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
				cairo_set_font_size(cr,0.5*52);
				cairo_set_font_size(cr,0.5*CSIZE);
				cairo_set_source_rgb(cr,1.0,0.0,0.0);
				cairo_move_to(cr,j*52+49,i*52+62);	
				cairo_show_text(cr,age);
				}
			
			}
		}
	}
	cairo_select_font_face(cr,"serif",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,0.5*CSIZE);
	cairo_set_source_rgb(cr,1.0,1.0,1.0);

	//le temps
	cairo_move_to(cr,30,(g.nbl+1)*52);
	cairo_show_text(cr,"temps passe : ");
	cairo_show_text(cr,temp);
	
	//le vieillissement
	cairo_move_to(cr,30,(g.nbl+2)*52);
	if(v==0)
	{	
		cairo_show_text(cr,"désactiver le vieillissement");
	}
	else
	{
		cairo_show_text(cr,"activer le vieillissement");
	}
	
	//cyclique
	cairo_select_font_face(cr,"serif",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,0.5*CSIZE);
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_move_to(cr,30,(g.nbl+3)*52);
	
	if(compte_voisins_vivants==compte_voisins_vivants_c)
		cairo_show_text(cr," i cyclique");
	else 
		cairo_show_text(cr," i non cyclique");
	
	//oscillant
	cairo_select_font_face(cr,"serif",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,0.5*40);
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_move_to(cr,30,(g.nbl+4)*52);
	if(o == 1)
	{
		if(affichageOscillant(g,v)==0)
		{			
			cairo_show_text(cr,"non oscillent");
		}
		else if(affichageOscillant(g,v)==2)
		{			
			char pas[1000];
			sprintf(pas,"%d",delai_Osciller(g,v));
			cairo_show_text(cr,"va etre oscillente dans ");
			cairo_show_text(cr,pas);
		}
	
		else if(affichageOscillant(g,v)==1)
		{
			char period[500];
			sprintf(period,"%d",periode(g,v));			
			cairo_show_text(cr,"oscillente , avec une periode de : ");
			cairo_show_text(cr,period);
		}
	}


	cairo_destroy(cr); // destroy cairo mask
}



int graphique(grille *g, grille *gc)
{
//1	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
        int v=0,o=0;
//2	// init the display
	if(!(dpy=XOpenDisplay(NULL)))
	{
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);



//3	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			paint(cs,*g,v,o);
		}
		if(e.xbutton.button == 1)
		{
			evolue(g,gc,v);
			temps++;
			paint(cs,*g,v,o);
		}
		if (e.xkey.keycode==57) { 
		// touche "n" charger une nouvelle grille
			libere_grille(g);
			libere_grille(gc);
			printf("Entrez le nom de la nouvelle grille à charger: ");
			temps=0;
			char nom[128];
			scanf("%s",nom);
			init_grille_from_file(nom, g);
			alloue_grille ((g->nbl),(g->nbc),gc);
			
			paint(cs,*g,v,o);
	      	}	


		if(e.xkey.keycode == 55)
		//la touche v vieillissement
		{
			v= 1 - v;	
			paint(cs,*g,v,o);

		}
		if(e.xkey.keycode == 54)//c
		{
			if(compte_voisins_vivants==compte_voisins_vivants_c)
			{
					compte_voisins_vivants=compte_voisins_v_n_c;
					paint(cs,*g,v,o);
			}				
			else
			{
					compte_voisins_vivants=compte_voisins_vivants_c;
					paint(cs,*g,v,o);
			}		
		}

		if(e.xkey.keycode == 32)//o
		{
			o = 1 - o;
			paint(cs,*g,v,o);
		}

		else if(e.xbutton.button==3) break;
	}



	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;
}

