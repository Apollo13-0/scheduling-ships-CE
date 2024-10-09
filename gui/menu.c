#include "menu.h"
#include "scheduler_gui.h"

GtkWidget *algorithm_label, *algorithm_combo, *channel_label, *channel_combo, *confirm_button, *param_label, *param_entry;

// Función que actualiza la interfaz cuando se selecciona un algoritmo de calendarización
void on_algorithm_changed(GtkComboBoxText *combo_box, gpointer user_data) {
    const gchar *selected_algorithm = gtk_combo_box_text_get_active_text(combo_box);

    gtk_widget_set_visible(param_label, FALSE);
    gtk_widget_set_visible(param_entry, FALSE);

    if (g_strcmp0(selected_algorithm, "Prioridad") == 0) {
        gtk_label_set_text(GTK_LABEL(param_label), "Ingrese la prioridad:");
        gtk_widget_set_visible(param_label, TRUE);
        gtk_widget_set_visible(param_entry, TRUE);
    } else if (g_strcmp0(selected_algorithm, "SJF") == 0) {
        gtk_label_set_text(GTK_LABEL(param_label), "Ingrese el tiempo del barco:");
        gtk_widget_set_visible(param_label, TRUE);
        gtk_widget_set_visible(param_entry, TRUE);
    } else if (g_strcmp0(selected_algorithm, "Tiempo real") == 0) {
        gtk_label_set_text(GTK_LABEL(param_label), "Ingrese el tiempo máximo:");
        gtk_widget_set_visible(param_label, TRUE);
        gtk_widget_set_visible(param_entry, TRUE);
    }
}

// Función que maneja el clic en el botón de confirmación
void on_button_clicked(GtkButton *button, gpointer user_data) {
    UserSelection *user_selection = (UserSelection *)user_data;
    user_selection->selected_calendarization = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(algorithm_combo));
    user_selection->extra_param_text = gtk_entry_get_text(GTK_ENTRY(param_entry));
    user_selection->selected_channel = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(channel_combo));

    g_print("Algoritmo de calendarización: %s\n", user_selection->selected_calendarization);
    g_print("Parámetro extra: %s\n", user_selection->extra_param_text);
    g_print("Algoritmo de canal: %s\n", user_selection->selected_channel);

    // Llamar a la función para crear la ventana del programador
    create_scheduler_window(user_selection);
}
// Función para crear el menú
void create_menu(GtkWidget *vbox, UserSelection *user_data) {
    algorithm_label = gtk_label_new("Seleccione el algoritmo de calendarización:");
    gtk_box_pack_start(GTK_BOX(vbox), algorithm_label, FALSE, FALSE, 0);

    algorithm_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(algorithm_combo), "RR");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(algorithm_combo), "Prioridad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(algorithm_combo), "SJF");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(algorithm_combo), "FCFS");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(algorithm_combo), "Tiempo real");
    gtk_box_pack_start(GTK_BOX(vbox), algorithm_combo, FALSE, FALSE, 0);

    // Create the parameter label with an empty string and entry field
    param_label = gtk_label_new("");  // Initialize with no text
    param_entry = gtk_entry_new();
    
    // Add them to the vbox, but ensure they are invisible initially
    gtk_box_pack_start(GTK_BOX(vbox), param_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), param_entry, FALSE, FALSE, 0);
    
    // Make sure both are invisible on app startup
    gtk_widget_set_visible(param_label, FALSE);
    gtk_widget_set_visible(param_entry, FALSE);

    // Connect the algorithm selection to the function that updates visibility
    g_signal_connect(algorithm_combo, "changed", G_CALLBACK(on_algorithm_changed), NULL);

    channel_label = gtk_label_new("Seleccione el algoritmo de canal:");
    gtk_box_pack_start(GTK_BOX(vbox), channel_label, FALSE, FALSE, 0);

    channel_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(channel_combo), "Equidad");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(channel_combo), "Letrero");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(channel_combo), "Tico");
    gtk_box_pack_start(GTK_BOX(vbox), channel_combo, FALSE, FALSE, 0);

    confirm_button = gtk_button_new_with_label("Confirmar");
    gtk_box_pack_start(GTK_BOX(vbox), confirm_button, FALSE, FALSE, 0);
    g_signal_connect(confirm_button, "clicked", G_CALLBACK(on_button_clicked), user_data);
}
