#include "io.h"

void paint(cairo_surface_t *surface, grille g){
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
				
				cairo_select_font_face(cr,"serif",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
				cairo_set_font_size(cr,0.5*52);
				cairo_set_source_rgb(cr,1.0,0.0,0.0);
				cairo_move_to(cr,j*52+49,i*52+62);				
			}
		}
	}

	cairo_destroy(cr); // destroy cairo mask
}


int v=0;

int graphique(grille *g, grille *gc)
{
//1	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

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
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);



//3	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) 
			paint(cs,*g);
	
		if(e.xbutton.button==1)
		{
			evolue(g,gc,v);
			paint(cs,*g);
		}
		else if(e.xbutton.button==3) break;
	}



	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;
}

