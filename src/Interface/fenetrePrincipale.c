#include "fenetrePrincipale.h"


int lancementFenetrePrincipale(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	/** 
	  Création et affichage de la fenetre de selection qui apparaît après la fenetre de lancement
	 */ 
	GtkBuilder *builder = gtk_builder_new();
	GtkWidget *mainWindow = NULL;
	GtkWidget *imageSearch = NULL;
	GtkWidget *logoSearch = NULL;
	GtkWidget *valeurAlpha = NULL;
	GtkWidget *valeurDelta = NULL;
	GtkWidget *tatouer = NULL;
	GtkWidget *afficherImage = NULL;
	GtkWidget *afficherLogo = NULL;
	GtkFileFilter *filtre = gtk_file_filter_new ();
	gchar directory[1024];

	recuperationBuilder(builder);

	//Pointeur vers les différents éléments de la fenêtre

	mainWindow = GTK_WIDGET(gtk_builder_get_object(builder,"mainWindow"));
	tatouer = GTK_WIDGET(gtk_builder_get_object(builder, "tatouer"));
	valeurAlpha = GTK_WIDGET(gtk_builder_get_object(builder,"valeur_alpha"));
	valeurDelta = GTK_WIDGET(gtk_builder_get_object(builder,"valeur_delta"));
	imageSearch = GTK_WIDGET(gtk_builder_get_object(builder,"search_image"));
	logoSearch = GTK_WIDGET(gtk_builder_get_object(builder,"search_logo"));
	afficherImage = GTK_WIDGET(gtk_builder_get_object(builder,"image"));
	afficherLogo = GTK_WIDGET(gtk_builder_get_object(builder,"logo"));

	//On active les signaux nécessaires au déroulement de l'appli

	g_signal_connect (mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL); 
	g_signal_connect (tatouer, "clicked", G_CALLBACK(tatouer_clicked_cb), NULL); 
	g_signal_connect (imageSearch, "file-set", G_CALLBACK(on_search_image_file_set), &positionImage);
	g_signal_connect (logoSearch, "file-set", G_CALLBACK(on_search_logo_file_set), &positionLogo);
	g_signal_connect (valeurDelta, "value-changed", G_CALLBACK(on_valeur_delta_change_value), &delta);
	g_signal_connect (valeurAlpha, "value-changed", G_CALLBACK(on_valeur_alpha_change_value), &alpha);
	g_signal_connect (imageSearch, "file-set", G_CALLBACK(search_image_file_set_cb), afficherImage);
	g_signal_connect (logoSearch, "file-set", G_CALLBACK(search_logo_file_set_cb), afficherLogo);

	//Redimention == FALSE
	gtk_window_set_resizable(GTK_WINDOW(mainWindow), FALSE);

	changeFilterAndDirectory(filtre, directory, imageSearch, logoSearch);



	gtk_widget_show_all(mainWindow);

	gtk_main();


	return 0;
}
