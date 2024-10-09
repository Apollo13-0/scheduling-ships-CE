#include "scheduler_gui.h"

// Función que crea la ventana del programador
void create_scheduler_window(UserSelection *user_data) {
    GtkWidget *window;
    GtkWidget *label;
    gchar *message;

    // Crear la nueva ventana
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Scheduler");
    gtk_window_set_default_size(GTK_WINDOW(window), 1800, 800);

    // Crear el mensaje con la selección del usuario
    message = g_strdup_printf("Algoritmo de calendarización: %s\nParámetro extra: %s\nAlgoritmo de canal: %s",
                              user_data->selected_calendarization ? user_data->selected_calendarization : "N/A",
                              user_data->extra_param_text ? user_data->extra_param_text : "N/A",
                              user_data->selected_channel ? user_data->selected_channel : "N/A");

    // Crear la etiqueta y agregarla a la ventana
    label = gtk_label_new(message);
    gtk_container_add(GTK_CONTAINER(window), label);

    // Liberar el mensaje
    g_free(message);

    // Mostrar la ventana
    gtk_widget_show_all(window);

    // Conectar la señal de cierre de la ventana
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
}
