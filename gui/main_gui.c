#include <gtk/gtk.h>
#include "menu.h"

// Función que inicializa la interfaz gráfica
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *vbox;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Scheduling Ships CE");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 10);  // Set border width instead of margins

    gtk_container_add(GTK_CONTAINER(window), vbox); // Use gtk_container_add() instead of gtk_window_set_child()

    // Crear el menú
    create_menu(vbox, user_data);

    // Mostrar la ventana
    gtk_widget_show_all(window); // gtk_widget_show_all() is needed to show the window and all children
}

// Función principal
int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    UserSelection user_selection = {NULL, NULL, NULL}; // Inicializa correctamente

    app = gtk_application_new("com.example.scheduling_ships_ce", G_APPLICATION_DEFAULT_FLAGS); // G_APPLICATION_DEFAULT_FLAGS is not available in GTK3
    g_signal_connect(app, "activate", G_CALLBACK(activate), &user_selection);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}
