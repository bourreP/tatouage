#include <gtk/gtk.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fenetrePrincipale.h"


int main( int argc, char *argv[] )
{
	/** 
	  Fonction principale
	 */

	//on initialise la bibliothèque GTK
	gtk_init(&argc, &argv);

	lancementFenetrePrincipale();

	return EXIT_SUCCESS;
}

