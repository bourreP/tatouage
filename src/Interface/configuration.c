#include "configuration.h"

GtkWidget *erreurImage = NULL;
GtkWidget *erreurLogo = NULL;
GtkWidget *erreurDetectImage = NULL;
GtkMessageDialog *sauvegardeImage=NULL;
gchar* positionImage = NULL;
gchar* positionLogo = NULL;
gchar* positionImageDetect=NULL;
gdouble alpha = 0.72;
gdouble delta = 115;

void changeFilterAndDirectory (GtkWidget* imageSearch, GtkWidget* logoSearch, GtkWidget* imageDetectSearch)
{
	GtkFileFilter *filtre = gtk_file_filter_new ();
	gchar* directory = NULL;

	directory = (gchar*) get_current_dir_name();

	gtk_file_filter_add_pattern (filtre,"*.bmp");
	gtk_file_filter_add_pattern (filtre,"*.jpg"); // on peut charger des images jpg  
	gtk_file_filter_add_pattern (filtre,"*.jpeg"); // on peut charger des images jpeg

	gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(imageSearch),filtre);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (imageSearch),directory);
	gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(logoSearch),filtre);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (logoSearch),directory);
	strcat(directory,"/Resultat");
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (imageDetectSearch),directory);
	gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(imageDetectSearch),filtre);
}

void recuperationBuilder(GtkBuilder* builder)
{
	gtk_builder_add_from_file (builder, "interface.glade", NULL);
}
