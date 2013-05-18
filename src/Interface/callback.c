#include "callback.h"


void on_search_image_file_set(GtkWidget *imageSearch, gchar** positionImage)
{
	*positionImage = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (imageSearch));
}

void on_search_logo_file_set(GtkWidget *logoSearch, gchar** positionLogo)
{
	*positionLogo = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (logoSearch));
}

void on_valeur_delta_change_value(GtkSpinButton *valeurDelta, gdouble* delta)
{
	*delta = gtk_spin_button_get_value(valeurDelta);
}

void on_valeur_alpha_change_value(GtkSpinButton *valeurAlpha, gdouble* alpha)
{
	*alpha = gtk_spin_button_get_value(valeurAlpha);
}

void search_image_file_set_cb(GtkWidget *buttonImage, GtkImage *afficherImage)
{
	GdkPixbuf *pixbuf;
	pixbuf = gdk_pixbuf_new_from_file(positionImage,NULL);
	pixbuf = gdk_pixbuf_scale_simple(pixbuf,100,100,GDK_INTERP_BILINEAR);

	gtk_image_set_from_pixbuf(afficherImage, pixbuf);
}

void search_logo_file_set_cb(GtkWidget *buttonImage, GtkImage *afficherLogo)
{
	GdkPixbuf *pixbuf;
	pixbuf = gdk_pixbuf_new_from_file(positionLogo,NULL);
	pixbuf = gdk_pixbuf_scale_simple(pixbuf,100,100,GDK_INTERP_BILINEAR);

	gtk_image_set_from_pixbuf(afficherLogo, pixbuf);
}

void tatouer_clicked_cb ()
{
	char* const argv[]= {"./Tatouage", positionImage, positionLogo};

	g_message("%s %s",argv[1], argv[2]);


	if (positionImage == NULL)
	{
		gtk_widget_show(erreurImage);
	}
	else if (positionLogo == NULL)
	{
		gtk_widget_show(erreurLogo);
	}
	else
	{
		system("mkdir Resultat 2> /dev/null");
		execvp("./Tatouage",argv);
	}
}

void on_buttonDialog1_clicked()
{
	gtk_widget_hide(erreurImage);
}
