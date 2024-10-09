#ifndef SCHEDULER_GUI_H
#define SCHEDULER_GUI_H

#include <gtk/gtk.h>
#include "user_selection.h"

#define CANAL_SPOTS 5  // Number of spots in the canal

typedef struct {
    GtkWidget *ship;     // Widget representing the ship
    int position;        // Current position in the canal
} Ship;

typedef struct {
    Ship **ships;        // Array of ships in the canal
    int ship_count;      // Number of ships in the canal
    int canal_capacity;  // Maximum number of ships in the canal
} Canal;

void create_scheduler_window(UserSelection *user_data);
void start_simulation(Canal *canal);

#endif // SCHEDULER_GUI_H
