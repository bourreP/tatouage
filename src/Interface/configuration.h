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

void recuperationBuilder(GtkBuilder* builder);
void changeFilterAndDirectory (GtkWidget* imageSearch, GtkWidget* logoSearch, GtkWidget* imageDetectSearch);

#endif
