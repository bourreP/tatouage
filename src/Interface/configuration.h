#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <gtk/gtk.h>
#include <string.h>

GtkWidget* erreurImage;
GtkWidget* erreurLogo;
GtkWidget *erreurDetectImage;
GtkMessageDialog* sauvegardeImage;
gchar* positionImage;
gchar* positionLogo;
gchar* positionImageDetect;

gdouble alpha;
gdouble delta;
gdouble compression;

void recuperationBuilder(GtkBuilder* builder);
void changeFilterAndDirectory (GtkWidget* imageSearch, GtkWidget* logoSearch);

#endif
