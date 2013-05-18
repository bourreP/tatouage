#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <gtk/gtk.h>

GtkWidget* erreurImage;
gchar* positionImage;
gchar* positionLogo;
gdouble alpha;
gdouble delta;

void recuperationBuilder(GtkBuilder* builder);
void changeFilterAndDirectory (GtkFileFilter *filtre, gchar *directory, GtkWidget* imageSearch, GtkWidget* logoSearch);

#endif
