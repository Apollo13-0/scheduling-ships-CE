#ifndef MENU_H
#define MENU_H

#include <gtk/gtk.h>
#include "user_selection.h"

// Funciones para crear el menú
void create_menu(GtkWidget *vbox, UserSelection *user_data);

#endif // MENU_H