#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>
#include <string.h>

#include "configuration.h"

void on_search_image_file_set(GtkWidget *buttonImage, gchar** positionImage);
void on_search_logo_file_set(GtkWidget *buttonImage, gchar** positionLogo);
void on_valeur_delta_change_value(GtkSpinButton *valeurDelta, gdouble* delta);
void on_valeur_alpha_change_value(GtkSpinButton *valeurAlpha, gdouble* alpha);
void search_image_file_set_cb(GtkWidget *buttonImage, GtkImage *afficherImage);
void search_logo_file_set_cb(GtkWidget *buttonImage, GtkImage *afficherLogo);
void tatouer_clicked_cb ();
void on_buttonDialog1_clicked();

#endif
