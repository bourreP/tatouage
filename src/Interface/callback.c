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
	gchar* alphaValue;
	gchar* deltaValue;

	alphaValue = g_strdup_printf("%lf",alpha);
	deltaValue = g_strdup_printf("%lf",delta);

	char* const argv[]= {"./Tatouage", positionImage, positionLogo, "insertion", alphaValue/*, deltaValue*/};

	if (positionImage == NULL)
	{
		gtk_widget_show(erreurImage);
		g_print("image non séléctionnée\n");
	}
	else if (positionLogo == NULL)
	{
		gtk_widget_show(erreurLogo);
		g_print("logo non choisi\n");
	}
	else
	{
		system("mkdir Resultat 2> /dev/null");
		execvp("./Tatouage",argv);
	}
	g_free(alphaValue);
	g_free(deltaValue);
}

void on_detecter_clicked()
{

	char* const argv[]= {"./Tatouage", positionImage, positionLogo, "detection"};

	execvp("./Tatouage",argv);
}
void on_buttonDialog1_clicked()
{
	gtk_widget_hide(erreurImage);
}

void on_buttonDialog2_clicked()
{
	gtk_widget_hide(erreurLogo);
}
