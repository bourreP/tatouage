#include "callback.h"


void on_search_image_file_set(GtkWidget *imageSearch, gchar** positionImage)
{
	*positionImage = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (imageSearch));
}

void on_search_logo_file_set(GtkWidget *logoSearch, gchar** positionLogo)
{
	*positionLogo = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (logoSearch));
}

void on_search_image_detect_file_set(GtkWidget *imageDetectSearch, gchar** positionImageDetect)
{
	*positionImageDetect = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (imageDetectSearch));
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
	gchar *my_stderr = NULL;
	gchar *my_stdout = NULL;
	GError *my_error = NULL;
	gint my_return_value;

	alphaValue = g_strdup_printf("%lf",alpha*100);
	deltaValue = g_strdup_printf("%lf",delta*100);

	char* argv[] = {"./Tatouage", positionImage, positionLogo, "insertion", alphaValue, deltaValue};

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
		g_spawn_sync(NULL, argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, &my_stdout, &my_stderr, &my_return_value, &my_error);
	}
	g_free(alphaValue);
	g_free(deltaValue);
	if(my_stderr)
		g_free(my_stderr);
	if(my_stdout)
		g_free(my_stdout);
	if(my_error)
		g_error_free(my_error);
}

void on_detecter_clicked()
{
	gchar *my_stderr = NULL;
	gchar *my_stdout = NULL;
	GError *my_error = NULL;
	gint my_return_value;

	positionImage = (gchar*) get_current_dir_name();

	g_strconcat(positionImage, (gchar*) "Resultat/imageTatouee.jpg", NULL);

	g_message("%s", g_file_test(positionImage, G_FILE_TEST_EXISTS));

	if(!g_file_test(positionImage, G_FILE_TEST_EXISTS))
	{
		gtk_widget_show(erreurDetectImage);
	}
	else
	{
		gtk_widget_show(GTK_WIDGET(sauvegardeImage));	
		char* argv[]= {"./Tatouage", positionImage, positionLogo, "detection"};
		g_spawn_sync(NULL, argv, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, &my_stdout, &my_stderr, &my_return_value, &my_error);

	}
	if(my_stderr)
		g_free(my_stderr);
	if(my_stdout)
		g_free(my_stdout);
	if(my_error)
		g_error_free(my_error);
}
void on_buttonDialog1_clicked()
{
	gtk_widget_hide(erreurImage);
}

void on_buttonDialog2_clicked()
{
	gtk_widget_hide(erreurLogo);
}

void on_buttonDialog3_clicked()
{
	gtk_widget_hide(erreurDetectImage);
}
