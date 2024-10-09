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
    gtk_widget_set_margin_start(GTK_WIDGET(vbox), 10);
    gtk_widget_set_margin_end(GTK_WIDGET(vbox), 10);
    gtk_widget_set_margin_top(GTK_WIDGET(vbox), 10);
    gtk_widget_set_margin_bottom(GTK_WIDGET(vbox), 10);

    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Crear el menú
    create_menu(vbox, user_data);

    // Mostrar la ventana
    gtk_window_present(GTK_WINDOW(window));
}

// Función principal
int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    UserSelection user_selection = {NULL, NULL, NULL}; // Inicializa correctamente

    app = gtk_application_new("com.example.scheduling_ships_ce", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), &user_selection);

    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;
}